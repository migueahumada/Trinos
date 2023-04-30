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

    float inSample = 0.0f;
    float outSample = 0.0f;
    float EULER = juce::MathConstants<float>::euler;
    
    for (int channel = 0; channel < buffer.getNumChannels(); channel++) {
        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            inSample = buffer.getSample(channel, i);
            
            if (inSample < 0)
            {
                outSample = -1 * inSample* waveshaperAmount;
                buffer.setSample(channel, i, outSample);
            }else
            {
                outSample = inSample * waveshaperAmount;
                buffer.setSample(channel, i, outSample);
            }
            
            
            
            /*
             --EXPONENTIAL--
            inSample = buffer.getSample(channel, i);
            
            outSample = waveshaperAmount * ((EULER - powf(EULER, 1 - inSample) ) / (EULER - 1));
            
            buffer.setSample(channel, i, outSample);
            */
            /*
             
            --SOFTCLIPPING--
             
            inSample = buffer.getSample(channel, i);
            
            outSample = (inSample - (powf(inSample, 3.0f)/3.0f)) * waveshaperAmount;
            
            buffer.setSample(channel, i, outSample);
             
             */
            
        }
    }
}

