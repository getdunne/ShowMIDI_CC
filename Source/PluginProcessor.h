#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <queue>

//==============================================================================
/**
*/
class CCPluginAudioProcessor    : public AudioProcessor
                                , public ChangeBroadcaster
{
public:
    //==============================================================================
    CCPluginAudioProcessor();
    ~CCPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    bool isMidiEffect() const override                     { return true; }

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override                  { return "CCVisualizer"; }

    bool acceptsMidi() const override                      { return true; }
    bool producesMidi() const override                     { return true; }
    double getTailLengthSeconds() const override           { return 0; }

    //==============================================================================
    int getNumPrograms() override                          { return 1; }
    int getCurrentProgram() override                       { return 0; }
    void setCurrentProgram (int) override                  {}
    const String getProgramName (int) override             { return {}; }
    void changeProgramName (int, const String&) override   {}

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    int lastUIWidth, lastUIHeight;

    struct CCUpdate { int ccNum; float ccValue; };
    std::queue<CCUpdate> ccQueue;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CCPluginAudioProcessor)
};
