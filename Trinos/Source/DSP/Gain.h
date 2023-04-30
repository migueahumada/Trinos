/*
  ==============================================================================

    Gain.h
    Created: 29 Apr 2023 7:32:29pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Gain
{
public:
    Gain();
    ~Gain();
    
    void setGain(float gainLevel);
    void process(juce::AudioBuffer<float>& buffer);
    
private:
    float gainValue {1.0f};
};


