#include <VintageKnackBass/Plugin.h>

#include <VintageKnackBass/Processor.h>

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
  return new Processor();
}
