/*
  ==============================================================================

    Waveform.cpp
    Created: 11 May 2023 10:29:10am
    Author:  Miguel Angel Ahumada Gaona

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Waveform.h"

//==============================================================================
Waveform::Waveform(TrinosAudioProcessor& p) : audioProcessor(p)
{
    mFormatManager.registerBasicFormats();
}

Waveform::~Waveform()
{
    mFormatReader = nullptr;
}

void Waveform::paint (juce::Graphics& g)
{

    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 10.0f, 0.0f);
    
    g.fillAll(juce::Colour(239, 247, 255));
    
    auto waveform = audioProcessor.irBuffer;
    
    if(waveform.getNumSamples() > 0)
    {
        juce::Path p;
        audioPoints.clear();
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
        
        for (int sample = 0 ; sample < waveform.getNumSamples(); sample+=ratio) {
            audioPoints.push_back(buffer[sample]);
        }
        
        g.setColour(juce::Colour(85, 140, 140));
        p.startNewSubPath(0, getHeight()/2);
        
        for (int sample = 0; sample < audioPoints.size(); ++sample) {
            auto point = juce::jmap(audioPoints[sample], -1.0f, 1.0f, 0.0f,(float)getHeight());
            p.lineTo(sample, point);
        }
        
        g.strokePath(p, juce::PathStrokeType(2));
        
        
    }
    else g.drawText("Drag & drop a sample!", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
}

void Waveform::resized()
{

}

bool Waveform::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (const auto& file : files)
    {
        juce::File currentFile(file);
        const juce::String fileExtension = currentFile.getFileExtension();

        if (fileExtension.equalsIgnoreCase(".wav")
            || fileExtension.equalsIgnoreCase(".mp3")
            || fileExtension.equalsIgnoreCase(".aiff")) {
            return true;
        }
    }

    return false;
}

void Waveform::filesDropped (const juce::StringArray& files, int x, int y)
{
    for (auto file:files)
    {
        if (isInterestedInFileDrag(file))
        {
            auto myFile = juce::File(file);
            mFormatReader = mFormatManager.createReaderFor(file);
            
            audioProcessor.irBuffer.setSize(mFormatReader->numChannels, (int)mFormatReader->lengthInSamples);
            mFormatReader->read(&audioProcessor.irBuffer,0,(int) mFormatReader->lengthInSamples, 0, true, true);
            audioProcessor.getConv().updateIR(myFile);
            
            
        }
    }
    repaint();
}
