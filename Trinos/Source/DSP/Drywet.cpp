/*
  ==============================================================================

    Drywet.cpp
    Created: 30 Apr 2023 4:08:39pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#include "Drywet.h"

Drywet::Drywet(){}
Drywet::~Drywet(){}

void Drywet::setDrywetValue(float drywetAmount)
{
    drywetValue = drywetAmount;
}
void Drywet::process(juce::AudioBuffer<float>& dryBuffer, juce::AudioBuffer<float>& wetBuffer)
{
    drywetValue = drywetValue / 100.0f;
    
    float wet = 1.0f;
    float dry = 1.0f;
    float outSample = 1.0f;
    
    for (int channel = 0; channel < dryBuffer.getNumChannels(); channel++) {
        for (int i = 0; i < dryBuffer.getNumSamples(); i++) {
            
            wet = wetBuffer.getSample(channel, i);
            dry = dryBuffer.getSample(channel, i);
            outSample = dry * (1.0f - drywetValue) + (drywetValue * wet);
            
            wetBuffer.setSample(channel, i, outSample);
            
        }
    }
}

