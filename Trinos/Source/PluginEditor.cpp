/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TrinosAudioProcessorEditor::TrinosAudioProcessorEditor (TrinosAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    prepareSliders();
    
    setSize (600, 400);
}

TrinosAudioProcessorEditor::~TrinosAudioProcessorEditor()
{
}
 
void TrinosAudioProcessorEditor::prepareSliders()
{
//SETEAR EL TIPO DE SLIDER
    outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterDrywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    waveshaperAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
//SETEAR EL TIPO DE CAJA DE TEXTO
    outputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    inputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    masterDrywetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    waveshaperAmountSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
//SETEAR TEXTO
    outputGainLabel.setText("Out Gain", juce::sendNotification);
    inputGainLabel.setText("In Gain", juce::sendNotification);
    masterDrywetLabel.setText("Dry/Wet", juce::sendNotification);
    waveshaperAmountLabel.setText("Clip", juce::sendNotification);

    //SETEAR LA JUSTIFACIÓN DEL TEXTO
    outputGainLabel.setJustificationType(juce::Justification::centred);
    inputGainLabel.setJustificationType(juce::Justification::centred);
    masterDrywetLabel.setJustificationType(juce::Justification::centred);
    waveshaperAmountLabel.setJustificationType(juce::Justification::centred);
    
    //LABEL ES LIGADO AL COMPONENTE
    outputGainLabel.attachToComponent(&outputGainSlider, false);
    inputGainLabel.attachToComponent(&inputGainSlider, false);
    masterDrywetLabel.attachToComponent(&masterDrywetSlider, false);
    waveshaperAmountLabel.attachToComponent(&waveshaperAmountSlider, false);
    
    
    outputGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    inputGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    masterDrywetLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    waveshaperAmountLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    addAndMakeVisible(outputGainLabel);
    addAndMakeVisible(inputGainLabel);
    addAndMakeVisible(masterDrywetLabel);
    addAndMakeVisible(waveshaperAmountLabel);
    
//HACER VISIBLE EL COMPONENTE
    addAndMakeVisible(outputGainSlider);
    addAndMakeVisible(inputGainSlider);
    addAndMakeVisible(masterDrywetSlider);
    addAndMakeVisible(waveshaperAmountSlider);

//ACTIVAR EL ATTACH MEDIANTE UN UNIQUE POINTER, ESTE PIDE UN APVTS, EL PARAMETER ID Y EL COMPONENTE VISUAL
    outputGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"OutputGain",outputGainSlider);
    inputGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"InputGain",inputGainSlider);
    masterDryWetAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"MasterDrywet",masterDrywetSlider);
    waveshaperAmountAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WaveshaperAmount",waveshaperAmountSlider);
    
    
    
}

void TrinosAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour(243,198,165));
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /*
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);*/
}

void TrinosAudioProcessorEditor::resized()
{
    outputGainSlider.setBoundsRelative(0.798773f, 0.750218f, 0.2f, 0.2f);
    inputGainSlider.setBoundsRelative(-2.99065e-08, 0.750218f,  0.2f, 0.2f);
    waveshaperAmountSlider.setBoundsRelative(0.416901f, 0.750218f, 0.2f, 0.2f);
    masterDrywetSlider.setBoundsRelative(0.798773f, 0.0933995f, 0.2f, 0.2f);
}
