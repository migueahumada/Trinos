/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TrinosAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TrinosAudioProcessorEditor (TrinosAudioProcessor&);
    ~TrinosAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void prepareSliders();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TrinosAudioProcessor& audioProcessor;
    
    juce::Slider masterDrywetSlider, outputGainSlider, inputGainSlider, waveshaperAmountSlider;
    juce::Label masterDrywetLabel, outputGainLabel, inputGainLabel, waveshaperAmountLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterDryWetAttach, outputGainAttach, inputGainAttach, waveshaperAmountAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrinosAudioProcessorEditor)
};
