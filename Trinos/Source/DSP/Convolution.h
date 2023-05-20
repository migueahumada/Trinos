/*
  ==============================================================================

    Convolution.h
    Created: 30 Apr 2023 3:30:06pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:
    Convolution();
    ~Convolution();
    
    void prepare(double inSampleRate, int inSamplePerBlock, int inNumChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateIR(juce::File audiofile);
    
private:
    juce::dsp::Convolution conv;
};
