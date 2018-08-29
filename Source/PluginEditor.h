#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CCSlider.h"

class CCListBoxModel : public ListBoxModel
{
public:
    CCListBoxModel(ListBox& lb) : ListBoxModel(), listBox(lb) {}
    virtual ~CCListBoxModel();

    int getNumRows() override { return sliders.size(); }
    void backgroundClicked(const MouseEvent&) override;

    void paintListBoxItem(int, Graphics &, int, int, bool) override;

    OwnedArray<CCSlider> sliders;

private:
    ListBox& listBox;
};

class CCPluginAudioProcessorEditor  : public AudioProcessorEditor
                                    , public ChangeListener
{
public:
    CCPluginAudioProcessorEditor(CCPluginAudioProcessor&);
    ~CCPluginAudioProcessorEditor();

    // Component
    void paint (Graphics&) override;
    void resized() override;

    // ChangeListener
    void changeListenerCallback(ChangeBroadcaster*) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CCPluginAudioProcessor& processor;

    TextButton addButton, delButton;
    CCListBoxModel listBoxModel;
    ListBox listBox;

    ComponentBoundsConstrainer resizeLimits;
    std::unique_ptr<ResizableCornerComponent> resizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CCPluginAudioProcessorEditor)
};
