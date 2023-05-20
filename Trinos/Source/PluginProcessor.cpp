/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TrinosAudioProcessor::TrinosAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

TrinosAudioProcessor::~TrinosAudioProcessor()
{
}

//==============================================================================

juce::AudioProcessorValueTreeState::ParameterLayout TrinosAudioProcessor::createParameters()
{
//TODO LO RELACIONADO CON LOS APVTS APARECERÁ AQUÍ.
    
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("InputGain", 1), "InputGain", 0.0f, 8.0f,1.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("ConvolutionDrywet",1), "ConvolutionDrywet", 0.0f, 100.0f, 100.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperAmount",1), "WaveshaperAmount", 1.0f, 3.0f, 1.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperDrywet",1), "WaveshaperDrywet", 0.0f, 100.0f, 100.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("MasterDrywet",1), "MasterDrywet", 0.0f, 100.0f, 100.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutputGain", 1), "OutputGain", 0.0f, 5.0f, 1.0f));
    
    
    return parameters;
    
}

const juce::String TrinosAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TrinosAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TrinosAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TrinosAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TrinosAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TrinosAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TrinosAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TrinosAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TrinosAudioProcessor::getProgramName (int index)
{
    return {};
}

void TrinosAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TrinosAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    conv.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    
    //Read wav from binary data and save samples in buffer.
    /*juce::MemoryInputStream inputStream(BinaryData::ExampleImpulseResponse_wav, BinaryData::ExampleImpulseResponse_wavSize, false);
    juce::WavAudioFormat wavFormat;
    juce::AudioFormatReader* reader = wavFormat.createReaderFor(&inputStream, false);
    
    irBuffer.setSize(reader->numChannels, (int)reader->lengthInSamples);
    reader->read    (&irBuffer, 0, (int)reader->lengthInSamples, 0, true, true);*/
      
    
}

void TrinosAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TrinosAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TrinosAudioProcessor::updateParameters()
{
    auto inputGainValue = apvts.getRawParameterValue("InputGain") -> load();
    
    auto convolutionDrywetValue= apvts.getRawParameterValue("ConvolutionDrywet") -> load();
    
    auto waveshaperAmountValue = apvts.getRawParameterValue("WaveshaperAmount") -> load();
    
    auto waveshaperDrywetValue= apvts.getRawParameterValue("WaveshaperDrywet") -> load();

    auto masterDrywetValue = apvts.getRawParameterValue("MasterDrywet") -> load();
    
    auto outputGainValue = apvts.getRawParameterValue("OutputGain") -> load();
    

    
    /*
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("InputGain", 1), "InputGain", 0.0f, 8.0f,1.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("ConvolutionDrywet",1), "ConvolutionDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperAmount",1), "WaveshaperAmount", 1.0f, 3.0f, 1.0f));

     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("WaveshaperDrywet",1), "WaveshaperDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("MasterDrywet",1), "MasterDrywet", 0.0f, 100.0f, 100.0f));
     
     parameters.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("OutputGain", 1), "OutputGain", 0.0f, 5.0f, 1.0f));
     
     */
    
    inputGain.setGain(inputGainValue);
    
    convolutionDrywet.setDrywetValue(convolutionDrywetValue);
    
    waveshaper.setWaveshaperAmount(waveshaperAmountValue);
    
    waveshaperDrywet.setDrywetValue(waveshaperDrywetValue);
    
    masterDrywet.setDrywetValue(masterDrywetValue);
    
    outputGain.setGain(outputGainValue);
    

}

void TrinosAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //SE HIZO UNA COPIA DEL BUFFER
    waveshaperDryBuffer.makeCopyOf(buffer);
    
    updateParameters();
    
    inputGain.process(buffer);
    
    waveshaper.process(buffer);
    conv.process(buffer);
    outputGain.process(buffer);
    
    masterDrywet.process(waveshaperDryBuffer, buffer);

    
    


}

Convolution& TrinosAudioProcessor::getConv()
{
    return conv;
}

//==============================================================================
bool TrinosAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TrinosAudioProcessor::createEditor()
{
    return new TrinosAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void TrinosAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TrinosAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}



//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TrinosAudioProcessor();
}
