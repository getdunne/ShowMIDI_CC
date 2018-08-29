#include "CCSlider.h"

// https://www.webnots.com/vibgyor-rainbow-color-codes/
static Colour rainbow[] =
{
    Colour(0xFF9400D3),
    Colour(0xFF4B0082),
    Colour(0xFF0000FF),
    Colour(0xFF00FF00),
    Colour(0xFFFFFF00),
    Colour(0xFFFF7F00),
    Colour(0xFFFF0000),
};

void CCSlider::paint(Graphics &g, int width, int height, bool rowIsSelected)
{
    int rainbowIndex = ccNumber % (sizeof(rainbow) / sizeof(Colour));

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
