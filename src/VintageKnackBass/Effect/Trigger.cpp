#include <VintageKnackBass/Effect/Trigger.h>

Trigger::Trigger(const double samplerate, const double window, const std::tuple<double, double> threshold)
{
  data.samplerate = samplerate;
  data.window = window;
  data.threshold = threshold;

  buffer.x.resize(static_cast<size_t>(window * samplerate));
  buffer.y = 0;
  buffer.state = false;
}

Trigger::~Trigger()
{
}

void Trigger::operator()(const std::span<const float> input, const std::span<float> output)
{
  const double weight = 1 / static_cast<double>(buffer.x.size());

  const auto threshold =
  {
    std::pow(10, std::get<0>(data.threshold) / 10),
    std::pow(10, std::get<1>(data.threshold) / 10)
  };

  const auto [lo, hi] = std::minmax(threshold);

  auto& x = buffer.x;
  auto& y = buffer.y;
  auto& s = buffer.state;

  for (size_t i = 0; i < input.size(); ++i)
  {
    const double x0 = x.front();
    const double x1 = static_cast<double>(input[i]);
    const double y0 = y;
    const double y1 = y0 + (x1 * x1 - x0 * x0) * weight;

    x.pop_front();
    x.push_back(x1);
    y = y1;

    if (y > hi && !s)
    {
      output[i] = 1;
      s = true;
    }
    else if (y < lo && s)
    {
      output[i] = 0;
      s = false;
    }
    else
    {
      output[i] = 0;
    }
  }
}
