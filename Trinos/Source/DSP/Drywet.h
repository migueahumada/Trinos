/*
  ==============================================================================

    Drywet.h
    Created: 30 Apr 2023 4:08:39pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Drywet
{
public:
    Drywet();
    ~Drywet();
    
    void setDrywetValue(float drywetAmount);
    void process(juce::AudioBuffer<float>& dryBuffer, juce::AudioBuffer<float>& wetBuffer);
    
private:
    float drywetValue = {1.0f};
    
};
