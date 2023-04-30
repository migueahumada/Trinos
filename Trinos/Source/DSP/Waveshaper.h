/*
  ==============================================================================

    Waveshaper.h
    Created: 29 Apr 2023 12:25:29pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Waveshaper
{
public:
    Waveshaper();
    ~Waveshaper();
    
    void setWaveshaperAmount(float apvtsWaveshaperAmount);
    void process(juce::AudioBuffer<float>& buffer);
    
private:
    float waveshaperAmount {1.0f};
    
};
