#include <VintageKnackBass/Editor.h>

#include <VintageKnackBass/Logger.h>

Editor::Editor(juce::AudioProcessor& process) :
  juce::GenericAudioProcessorEditor(process)
{
  setSize(500, 500);
}

Editor::~Editor()
{
}
