#pragma once

#include <span>

class Effect final
{

public:

  Effect(const double samplerate, const int blocksize);
  ~Effect();

  int latency() const;

  void dry(const std::span<const float> input, const std::span<float> output);
  void wet(const std::span<const float> input, const std::span<float> output);

private:

  const double samplerate;
  const int blocksize;

};
