#include <VintageKnackBass/Effect/ASR.h>

ASR::ASR(const double samplerate, const double attack, const double sustain, const double release)
{
  data.samplerate = samplerate;
  data.attack = attack;
  data.sustain = sustain;
  data.release = release;

  const size_t a = static_cast<size_t>(attack  * samplerate);
  const size_t s = static_cast<size_t>(sustain * samplerate);
  const size_t r = static_cast<size_t>(release * samplerate);
  const size_t n = a + s + r;

  buffer.shape.resize(n, 1);
  buffer.cursor = n;

  for (size_t i = 0, j = 0; i < a; ++i, ++j)
  {
    buffer.shape.at(j) = static_cast<float>(i) / static_cast<float>(a);
  }

  for (size_t i = 0, j = n - 1; i < r; ++i, --j)
  {
    buffer.shape.at(j) = static_cast<float>(i) / static_cast<float>(r);
  }
}

ASR::~ASR()
{
}

void ASR::operator()(const std::span<const float> input, const std::span<float> output)
{
  const auto& shape = buffer.shape;
  const auto n = shape.size();

  auto& j = buffer.cursor;

  for (size_t i = 0; i < input.size(); ++i)
  {
    if (input[i])
    {
      j = 0;
    }

    output[i] = (j < n) ? shape[j++] : 0;
  }
}
