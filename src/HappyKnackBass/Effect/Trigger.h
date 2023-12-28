#pragma once

#include <algorithm>
#include <deque>
#include <span>
#include <tuple>

class Trigger final
{

public:

  Trigger(const double samplerate, const double window, const std::tuple<double, double> threshold);
  ~Trigger();

  void operator()(const std::span<const float> input, const std::span<float> output);

private:

  struct
  {
    double samplerate;
    double window;
    std::tuple<double, double> threshold;
  }
  data;

  struct
  {
    std::deque<double> x;
    double y;
    bool state;
  }
  buffer;

};
