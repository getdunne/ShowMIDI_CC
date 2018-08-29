/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CCPluginAudioProcessor::CCPluginAudioProcessor()
    : AudioProcessor (BusesProperties()) // add no audio buses at all
{
    lastUIWidth = 200;
    lastUIHeight = 150;
}

CCPluginAudioProcessor::~CCPluginAudioProcessor()
{
}

//==============================================================================
void CCPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void CCPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void CCPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midi)
{
    // the audio buffer in a midi effect will have zero channels!
    jassert (buffer.getNumChannels() == 0);

    MidiMessage msg;
    int ignore;
    bool gotControllerMsg = false;

    for (MidiBuffer::Iterator it (midi); it.getNextEvent (msg, ignore);)
    {
        if (msg.isController())
        {
            gotControllerMsg = true;

            CCUpdate update;
            update.ccNum = msg.getControllerNumber();
            update.ccValue = msg.getControllerValue() / 127.0f;
            ccQueue.push(update);
        }
    }

    if (gotControllerMsg) sendChangeMessage();
}

//==============================================================================
bool CCPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CCPluginAudioProcessor::createEditor()
{
    return new CCPluginAudioProcessorEditor (*this);
}

//==============================================================================
void CCPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    XmlElement xml = XmlElement("uiSize");
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    copyXmlToBinary(xml, destData);
}

void CCPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xml = getXmlFromBinary(data, sizeInBytes);
    lastUIWidth  = xml->getIntAttribute ("uiWidth", lastUIWidth);
    lastUIHeight = xml->getIntAttribute ("uiHeight", lastUIHeight);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CCPluginAudioProcessor();
}
