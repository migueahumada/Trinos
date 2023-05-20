/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TrinosAudioProcessorEditor::TrinosAudioProcessorEditor (TrinosAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    prepareSliders();
    
    addAndMakeVisible(waveform);
    
    setSize (600, 400);
}

TrinosAudioProcessorEditor::~TrinosAudioProcessorEditor()
{
}
 
void TrinosAudioProcessorEditor::prepareSliders()
{
    
    /*
     
     inputGain.setGain(inputGainValue);
     
     convolutionDrywet.setDrywetValue(convolutionDrywetValue);
     
     waveshaper.setWaveshaperAmount(waveshaperAmountValue);
     
     waveshaperDrywet.setDrywetValue(waveshaperDrywetValue);
     
     masterDrywet.setDrywetValue(masterDrywetValue);
     
     outputGain.setGain(outputGainValue);
     
     */
//SETEAR EL TIPO DE SLIDER
    inputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    convolutionDrywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    waveshaperAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    //waveshaperDrywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    masterDrywetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
//SETEAR EL TIPO DE CAJA DE TEXTO
    inputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
    convolutionDrywetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
    waveshaperAmountSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
    //waveshaperDrywetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
    masterDrywetSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
    outputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0.0f, 0.0f);
    
//SETEAR TEXTO
    
    inputGainLabel.setText("In Gain", juce::sendNotification);
    
    convolutionDrywetLabel.setText("Conv Dry/Wet", juce::sendNotification);
    
    waveshaperAmountLabel.setText("Waveshaper", juce::sendNotification);
    
    //waveshaperDrywetLabel.setText("Waveshaper Dry/Wet", juce::sendNotification);
    
    masterDrywetLabel.setText("Dry/Wet", juce::sendNotification);
    
    outputGainLabel.setText("Out Gain", juce::sendNotification);

    //SETEAR LA JUSTIFACIÓN DEL TEXTO
    
    inputGainLabel.setJustificationType(juce::Justification::centred);
    
    convolutionDrywetLabel.setJustificationType(juce::Justification::centred);
    
    waveshaperAmountLabel.setJustificationType(juce::Justification::centred);
    
    //waveshaperDrywetLabel.setJustificationType(juce::Justification::centred);
    
    masterDrywetLabel.setJustificationType(juce::Justification::centred);
    
    outputGainLabel.setJustificationType(juce::Justification::centred);
    
    //LABEL ES LIGADO AL COMPONENTE
    
    
    inputGainLabel.attachToComponent(&inputGainSlider, false);
    
    convolutionDrywetLabel.attachToComponent(&convolutionDrywetSlider, false);
    
    waveshaperAmountLabel.attachToComponent(&waveshaperAmountSlider, false);
    
    //waveshaperDrywetLabel.attachToComponent(&waveshaperDrywetSlider, false);
    
    masterDrywetLabel.attachToComponent(&masterDrywetSlider, false);
    
    outputGainLabel.attachToComponent(&outputGainSlider, false);
    
    //Colour
    
    
    
    
    inputGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    convolutionDrywetLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    waveshaperAmountLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    //waveshaperDrywetLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    masterDrywetLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    outputGainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    
    //Hacer visible el texto
    
    
    
    addAndMakeVisible(inputGainLabel);
    
    addAndMakeVisible(convolutionDrywetLabel);
    
    //addAndMakeVisible(waveshaperDrywetLabel);
    
    addAndMakeVisible(waveshaperAmountLabel);
    
    addAndMakeVisible(masterDrywetLabel);
    
    addAndMakeVisible(outputGainLabel);
    
//HACER VISIBLE EL slider
    
    
    
    addAndMakeVisible(inputGainSlider);
    
    addAndMakeVisible(convolutionDrywetSlider);
    
    addAndMakeVisible(waveshaperAmountSlider);
    
    //addAndMakeVisible(waveshaperAmountSlider);
    
    addAndMakeVisible(masterDrywetSlider);
    
    addAndMakeVisible(outputGainSlider);

//ACTIVAR EL ATTACH MEDIANTE UN UNIQUE POINTER, ESTE PIDE UN APVTS, EL PARAMETER ID Y EL COMPONENTE VISUAL
    
    /*
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("InputGain", 1), "InputGain", 0.0f, 8.0f,1.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("ConvolutionDrywet",1), "ConvolutionDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperAmount",1), "WaveshaperAmount", 1.0f, 3.0f, 1.0f));

     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperDrywet",1), "WaveshaperDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("MasterDrywet",1), "MasterDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutputGain", 1), "OutputGain", 0.0f, 5.0f, 1.0f));
     
     */
    
    inputGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"InputGain",inputGainSlider);
    
    convolutionDrywetAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"ConvolutionDrywet",convolutionDrywetSlider);
    
    waveshaperAmountAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WaveshaperAmount",waveshaperAmountSlider);
    
    //waveshaperAmountAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WaveshaperDrywet",waveshaperAmountSlider);
    
    masterDryWetAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"MasterDrywet",masterDrywetSlider);
    
    outputGainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts,"OutputGain",outputGainSlider);
    
    
    
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
    
    waveform.setBoundsRelative(0.05f, 0.05f, 0.7f, 0.5f);
    
    inputGainSlider.setBoundsRelative(-2.99065e-08, 0.750218f,  0.2f, 0.2f);
    
    
    
    
    
    masterDrywetSlider.setBoundsRelative(0.798773f, 0.0933995f, 0.2f, 0.2f);
    
    outputGainSlider.setBoundsRelative(0.798773f, 0.750218f, 0.2f, 0.2f);
}
