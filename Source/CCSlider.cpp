#include "CCSlider.h"

// https://www.webnots.com/vibgyor-rainbow-color-codes/
static Colour rainbow[] =
{
    Colour(0xFFB450E3),     // purple
    Colour(0xFF5B4092),
    Colour(0xFF4F3FFF),     // blue
    Colour(0xFF00FF00),     // green
    Colour(0xFFFFFF00),     // yellow
    Colour(0xFFFF7F00),     // dark orange
    Colour(0xFFFF0000),     // red
};

void CCSlider::paint(Graphics &g, int width, int height, bool rowIsSelected)
{
    int rainbowIndex = ccNumber % (sizeof(rainbow) / sizeof(Colour));
    DBG("ccNumber " + String(ccNumber) + " rainbowIndex " + String(rainbowIndex));

    g.setColour(rowIsSelected ? Colours::hotpink : Colours::lightgrey);
    Rectangle<int> area(0, 0, width, height);
    area.reduce(2, 4);

    g.fillRect(area);

    if (!rowIsSelected && value > 0.0f)
    {
        g.setColour(rainbow[rainbowIndex]);
        Rectangle<int> bar(area.getX(),
            area.getY(),
            int(value * area.getWidth()),
            area.getHeight());
        g.fillRect(bar);

    }

    if (rowIsSelected)
    {
        g.setColour(Colours::white);
        g.drawText("MIDI LEARN...", area.toFloat(), Justification::centred);
        g.drawRect(area);
    }
    else
    {
        g.setColour(Colours::black);
        g.drawText("CC " + String(ccNumber), area.toFloat(), Justification::centred);
    }
}


void CCSlider::setValue(float v)
{
    value = v;
    if (value < 0.0f) value = 0.0f;
    if (value > 1.0f) value = 1.0f;
}
