/*
  ==============================================================================

    Waveform.h
    Created: 11 May 2023 10:29:10am
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class Waveform  : public juce::Component, public juce::FileDragAndDropTarget
{
    
public:
    Waveform(TrinosAudioProcessor&);
    ~Waveform() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    TrinosAudioProcessor& audioProcessor;
    
    std::vector<float> audioPoints;
    
    juce::AudioFormatManager mFormatManager;
    juce::AudioFormatReader* mFormatReader{nullptr	};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waveform)
};
