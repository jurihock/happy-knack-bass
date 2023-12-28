#include <HappyKnackBass/Editor.h>

#include <HappyKnackBass/Logger.h>

Editor::Editor(juce::AudioProcessor& process) :
  juce::GenericAudioProcessorEditor(process)
{
  setSize(500, 500);
}

Editor::~Editor()
{
}
