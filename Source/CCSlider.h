#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct CCSlider
{
public:
    CCSlider(int ccNum) : value(0.0f), ccNumber(ccNum) {}

    void paint(Graphics &, int, int, bool);
	void setValue(float v);

	float value;
    int ccNumber;
};
