/*
  ==============================================================================

    Waveshaper.cpp
    Created: 29 Apr 2023 12:25:29pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#include "Waveshaper.h"

Waveshaper::Waveshaper(){}
Waveshaper::~Waveshaper(){}

void Waveshaper::setWaveshaperAmount(float apvtsWaveshaperAmount)
{
    waveshaperAmount = apvtsWaveshaperAmount;
}

void Waveshaper::process(juce::AudioBuffer<float>& buffer)
{
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            float inSample = buffer.getSample(channel, i);
            
            float outSample = inSample * waveshaperAmount;
            
            buffer.setSample(channel, i, outSample);
            
        }
    }
}

