#pragma once

#include <array>
#include <cmath>
#include <numbers>
#include <span>

class Filter final
{

public:

  Filter(const double samplerate, const double frequency, const double gain, const double quality);
  ~Filter();

  void operator()(const std::span<const float> input, const std::span<float> output);

private:

  struct
  {
    double samplerate, frequency, gain, quality;
  }
  data;

  struct
  {
    std::array<double, 3> b, a, x, y;
  }
  buffer;

};
