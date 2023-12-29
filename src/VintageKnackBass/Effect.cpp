#include <VintageKnackBass/Effect.h>

Effect::Effect(const double samplerate, const int blocksize) :
  filter(samplerate, 1000, 24, 10),
  trigger(samplerate, 20e-3, { -15, -25 }),
  asr(samplerate, 1e-3, 2e-3, 1e-3)
{
  data.samplerate = samplerate;
  data.blocksize = blocksize;

  buffer.response.resize(static_cast<size_t>(blocksize));
  buffer.envelope.resize(static_cast<size_t>(blocksize));
}

Effect::~Effect()
{
}

int Effect::latency() const
{
  return 0;
}

void Effect::dry(const std::span<const float> input, const std::span<float> output)
{
  std::copy(input.begin(), input.end(), output.begin());
}

void Effect::wet(const std::span<const float> input, const std::span<float> output)
{
  auto& response = buffer.response;
  auto& envelope = buffer.envelope;

  response.resize(input.size());
  envelope.resize(input.size());

  filter(input, response);
  trigger(input, envelope);
  asr(envelope, envelope);

  for (size_t i = 0; i < input.size(); ++i)
  {
    const float x = input[i] * (1 - envelope[i]);
    const float y = response[i] * envelope[i];

    output[i] = std::clamp(x + y, -1.f, +1.f);
  }
}
