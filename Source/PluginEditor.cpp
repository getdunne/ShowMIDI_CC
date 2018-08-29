#include "PluginProcessor.h"
#include "PluginEditor.h"

CCListBoxModel::~CCListBoxModel()
{
    sliders.clear();
}

void CCListBoxModel::backgroundClicked(const MouseEvent&)
{
    listBox.deselectAllRows();
}

void CCListBoxModel::paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    sliders[rowNumber]->paint(g, width, height, rowIsSelected);
}

CCPluginAudioProcessorEditor::CCPluginAudioProcessorEditor(CCPluginAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processor (p)
    , listBoxModel(listBox)
{
    addButton.setButtonText("Add");
    addButton.onClick = [this] {
        listBoxModel.sliders.add(new CCSlider(1));
        listBox.updateContent();
        listBox.selectRow(listBoxModel.sliders.size() - 1);
    };
    addAndMakeVisible(addButton);

    delButton.setButtonText("Remove");
    delButton.onClick = [this] {
        int row = listBox.getSelectedRow();
        if (row < 0) listBoxModel.sliders.removeLast();
        else
        {
            listBox.deselectRow(row);
            listBoxModel.sliders.remove(row);
        }
        listBox.updateContent();
    };
    addAndMakeVisible(delButton);

    listBox.setModel(&listBoxModel);
    listBox.setRowHeight(40);
    addAndMakeVisible(listBox);
    changeListenerCallback(nullptr);

    resizeLimits.setSizeLimits (100, 100, 600, 800);
    resizer.reset(new ResizableCornerComponent(this, &resizeLimits));
    addAndMakeVisible(*resizer);

    addButton.onClick();

    processor.addChangeListener(this);

    setSize (processor.lastUIWidth, processor.lastUIHeight);
}

CCPluginAudioProcessorEditor::~CCPluginAudioProcessorEditor()
{
    processor.removeChangeListener(this);
}

void CCPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void CCPluginAudioProcessorEditor::resized()
{
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    processor.lastUIWidth = getWidth();
    processor.lastUIHeight = getHeight();

    auto area = getLocalBounds();
    area.reduce(5, 5);
    addButton.setBounds(area.removeFromTop(21));
    delButton.setBounds(area.removeFromBottom(21));
    area.reduce(0, 4);
    listBox.setBounds(area);
}

void CCPluginAudioProcessorEditor::changeListenerCallback(ChangeBroadcaster*)
{
    int selectedRow = listBox.getSelectedRow();

    while (!processor.ccQueue.empty())
    {
        CCPluginAudioProcessor::CCUpdate update = processor.ccQueue.front();
        processor.ccQueue.pop();

        for (int i = 0; i < listBoxModel.sliders.size(); i++)
        {
            int ccNum = listBoxModel.sliders[i]->ccNumber;
            if (i == selectedRow)
            {
                listBoxModel.sliders[i]->ccNumber = update.ccNum;
                listBoxModel.sliders[i]->setValue(update.ccValue);
                listBox.deselectAllRows();
            }
            else if (ccNum == update.ccNum)
            {
                listBoxModel.sliders[i]->setValue(update.ccValue);
            }
        }
    }
    listBox.repaint();
}
