import biquad
import numpy as np
import matplotlib.pyplot as plot

from dhbw import dasp

def norm(x, factor=1):

    x = np.atleast_1d(x)
    assert x.ndim == 1

    if factor is None:
        factor = 1 / np.max(np.abs(x))

    y = x * factor

    return y

def mrms(x, window, sr):

    n = int(window * sr)

    x = np.atleast_1d(x)
    assert x.ndim == 1

    y = x.copy()
    y.resize(len(x) + n)

    y = np.square(y)
    y = y - np.roll(y, n)
    y = np.cumsum(y / n)

    return y[:len(x)]

def trig(x, thresh):

    lohi = [
        10 ** (np.ravel(thresh)[0] / 10),
        10 ** (np.ravel(thresh)[-1] / 10)
    ]

    lo = np.min(lohi)
    hi = np.max(lohi)

    state = False

    x = np.atleast_1d(x)
    assert x.ndim == 1

    y = np.zeros_like(x)

    for i in range(len(x)):

        if x[i] > hi and not state:
            y[i] = 1
            state = True

        elif x[i] < lo and state:
            y[i] = 0
            state = False

        else:
            y[i] = 0

    return y

def asr(x, a, s, r, sr):

    x = np.atleast_1d(x)
    assert x.ndim == 1

    a = int(a * sr)
    s = int(s * sr)
    r = int(r * sr)

    a = np.ones(a) # np.linspace(0, 1, a)
    s = np.ones(s)
    r = np.ones(r) # np.linspace(1, 0, r)

    shape = np.concatenate((a, s, r))
    peaks = np.flatnonzero(x)

    y = np.zeros_like(x)

    for peak in peaks:

        begin  = peak
        end    = peak + len(shape)
        weight = x[peak]

        y[begin:end] = np.maximum(y[begin:end], weight * shape)

    return y

if __name__ == '__main__':

    file = 'oldie'

    x, t, sr = dasp.io.read(file)
    print(file, len(x), round(t[-1], 3), sr)

    x = norm(x)
    e = mrms(x, 20e-3, sr)

    db = 10 * np.log10(e)

    e = trig(e, (-15, -25))
    e = asr(e, 1e-3, 2e-3, 1e-3, sr)

    if False:

        plot.figure()
        plot.plot(x)
        plot.plot(e)
        plot.ylim(-1.1, +1.1)
        plot.figure()
        plot.plot(db)
        plot.ylim(-100, +0)
        plot.show()
        exit()

    f = biquad.highpass(sr, f=1000, g=24, q=10)(x)

    dry = x.copy()
    wet = f.copy()

    on  = e > 0
    off = np.invert(on)

    dry[on] *= 1 - e[on]
    wet[on] *= e[on]
    wet[off] = 0

    y = dry + wet

    dasp.io.write(f'{file}.flt', f, sr)
    dasp.io.write(f'{file}.mix', y, sr)

    # dasp.io.play(f'{file}.flt')
    dasp.io.play(f'{file}.mix')
