#include <HappyKnackBass/Effect.h>

#include <juce_core/juce_core.h>

Effect::Effect(const double samplerate, const int blocksize) :
  samplerate(samplerate), blocksize(blocksize)
{
}

Effect::~Effect()
{
  juce::ignoreUnused(samplerate, blocksize);
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
  std::copy(input.begin(), input.end(), output.begin());
}
