/*
  ==============================================================================

    Gain.cpp
    Created: 29 Apr 2023 7:32:29pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#include "Gain.h"

Gain::Gain(){}
Gain::~Gain(){}

void Gain::setGain(float gainLevel)
{
    gainValue = gainLevel;
}

void Gain::process(juce::AudioBuffer<float>& buffer)
{
    float inSample = 0.0f;
    float outSample = 0.0f;
    
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            inSample = buffer.getSample(channel, i);
            
            outSample = gainValue * inSample;
            
            buffer.setSample(channel, i, outSample);
            
            
        }
    }
}

