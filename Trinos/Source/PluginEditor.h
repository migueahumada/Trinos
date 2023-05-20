/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Components/Waveform.h"

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

    TrinosAudioProcessor& audioProcessor;
    
    Waveform waveform {audioProcessor};
    
    juce::Slider convolutionDrywetSlider,waveshaperDrywetSlider, masterDrywetSlider, outputGainSlider, inputGainSlider, waveshaperAmountSlider;
    
    juce::Label convolutionDrywetLabel, waveshaperDrywetLabel, masterDrywetLabel, outputGainLabel, inputGainLabel, waveshaperAmountLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> convolutionDrywetAttach, waveshaperDrywetAttach, masterDryWetAttach, outputGainAttach, inputGainAttach, waveshaperAmountAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrinosAudioProcessorEditor)
};
