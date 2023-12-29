#include <VintageKnackBass/Effect/Filter.h>

Filter::Filter(const double samplerate, const double frequency, const double gain, const double quality)
{
  data.samplerate = samplerate;
  data.frequency = frequency;
  data.gain = gain;
  data.quality = quality;
}

Filter::~Filter()
{
}

void Filter::operator()(const std::span<const float> input, const std::span<float> output)
{
  const double f = data.frequency;
  const double g = std::pow(10, data.gain / 20);
  const double q = data.quality;

  const double r = 2 * std::numbers::pi / data.samplerate;
  const double w = f * r;

  const double sinw = std::sin(w);
  const double cosw = std::cos(w);

  const double alpha = sinw / (+2 * q);
  const double beta  = cosw * (-2);
  const double gamma = cosw + (+1);

  auto& b = buffer.b;
  auto& a = buffer.a;
  auto& x = buffer.x;
  auto& y = buffer.y;

  b[0] = gamma / (+2);
  b[1] = gamma * (-1);
  b[2] = gamma / (+2);

  a[0] = 1 + alpha;
  a[1] =     beta;
  a[2] = 1 - alpha;

  for (size_t i = 0; i < input.size(); ++i)
  {
    x[2] = x[1];
    x[1] = x[0];

    y[2] = y[1];
    y[1] = y[0];

    x[0] = static_cast<double>(input[i]);

    const double bx = b[0] * x[0] +
                      b[1] * x[1] +
                      b[2] * x[2];

    const double ay = a[1] * y[1] +
                      a[2] * y[2];

    y[0] = (bx * g - ay) / a[0];

    output[i] = static_cast<float>(y[0]);
  }
}
