#pragma once

#include <HappyKnackBass/Effect/Filter.h>
#include <HappyKnackBass/Effect/Trigger.h>
#include <HappyKnackBass/Effect/ASR.h>

class Effect final
{

public:

  Effect(const double samplerate, const int blocksize);
  ~Effect();

  int latency() const;

  void dry(const std::span<const float> input, const std::span<float> output);
  void wet(const std::span<const float> input, const std::span<float> output);

private:

  Filter filter;
  Trigger trigger;
  ASR asr;

  struct
  {
    double samplerate;
    int blocksize;
  }
  data;

  struct
  {
    std::vector<float> response;
    std::vector<float> envelope;
  }
  buffer;

};
