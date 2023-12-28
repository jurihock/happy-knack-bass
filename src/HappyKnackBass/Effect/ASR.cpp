#include <HappyKnackBass/Effect/ASR.h>

ASR::ASR(const double samplerate, const double attack, const double sustain, const double release)
{
  data.samplerate = samplerate;
  data.attack = attack;
  data.sustain = sustain;
  data.release = release;

  buffer.cursor = std::numeric_limits<size_t>::max();
}

ASR::~ASR()
{
}

void ASR::operator()(const std::span<const float> input, const std::span<float> output)
{
  const size_t a = static_cast<size_t>(data.attack * data.samplerate);
  const size_t s = static_cast<size_t>(data.sustain * data.samplerate);
  const size_t r = static_cast<size_t>(data.release * data.samplerate);
  const size_t n = a + s + r;

  auto& j = buffer.cursor;

  for (size_t i = 0; i < input.size(); ++i)
  {
    if (input[i] > 0)
    {
      j = 0;
    }

    if (j >= n)
    {
      output[i] = 0;
      return;
    }

    output[i] = 1;
    ++j;
  }
}
