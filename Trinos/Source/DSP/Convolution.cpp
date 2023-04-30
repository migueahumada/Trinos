/*
  ==============================================================================

    Convolution.cpp
    Created: 30 Apr 2023 3:30:06pm
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#include "Convolution.h"

Convolution::Convolution(){}
Convolution::~Convolution(){}

void Convolution::prepare(double inSampleRate, int inSamplePerBlock, int inNumChannels)
{
    juce::dsp::ProcessSpec spec;
    
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplePerBlock;
    spec.numChannels = inNumChannels;
    
    conv.reset();
    conv.prepare(spec);
    
    conv.loadImpulseResponse(BinaryData::ExampleImpulseResponse_wav,
                             BinaryData::ExampleImpulseResponse_wavSize,
                             juce::dsp::Convolution::Stereo::yes,
                             juce::dsp::Convolution::Trim::yes,
                             0,
                             juce::dsp::Convolution::Normalise::yes);
    
}
void Convolution::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    conv.process(context);
}
