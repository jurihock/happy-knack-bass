#pragma once

#include <limits>
#include <span>

class ASR final
{

public:

  ASR(const double samplerate, const double attack, const double sustain, const double release);
  ~ASR();

  void operator()(const std::span<const float> input, const std::span<float> output);

private:

  struct
  {
    double samplerate, attack, sustain, release;
  }
  data;

  struct
  {
    size_t cursor;
  }
  buffer;

};
