#include <VintageKnackBass/Parameters.h>

#include <VintageKnackBass/Logger.h>

Parameters::Parameters(juce::AudioProcessor& process) :
  GenericParameterContainer(process)
{
  add("bypass", new juce::AudioParameterBool(
    { "bypass", schema }, "Bypass", false,
    juce::AudioParameterBoolAttributes()));
}

Parameters::~Parameters()
{
}

void Parameters::onbypass(std::function<void()> callback)
{
  call("bypass", callback);
}

bool Parameters::bypass() const
{
  return get<bool>("bypass");
}

void Parameters::load(const void* data, const int size)
{
  try
  {
    auto xml = std::unique_ptr<juce::XmlElement>(
      juce::AudioProcessor::getXmlFromBinary(data, size));

    if (xml)
    {
      LOG(xml->toString(juce::XmlElement::TextFormat().withoutHeader()));
    }
    else
    {
      return;
    }

    if (xml->hasTagName("VintageKnackBass") == false) { return; }
    if (xml->getIntAttribute("schema") != schema) { return; }

    read<bool>("bypass", *xml);
  }
  catch(const std::exception& exception)
  {
    juce::ignoreUnused(exception);

    LOG(exception.what());
  }
}

void Parameters::save(juce::MemoryBlock& data)
{
  try
  {
    auto xml = std::make_unique<juce::XmlElement>("VintageKnackBass");

    xml->setAttribute("schema", schema);

    write<bool>("bypass", *xml);

    LOG(xml->toString(juce::XmlElement::TextFormat().withoutHeader()));

    juce::AudioProcessor::copyXmlToBinary(*xml, data);
  }
  catch(const std::exception& exception)
  {
    juce::ignoreUnused(exception);

    LOG(exception.what());
  }
}
