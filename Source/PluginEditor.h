/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace std;
//==============================================================================
/**
*/
class BW_FilterTaskAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BW_FilterTaskAudioProcessorEditor
    (BW_FilterTaskAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~BW_FilterTaskAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BW_FilterTaskAudioProcessor& audioProcessor;
    
    juce::Slider cutoffFrequencySlider; ///Create a slider for the Cutoff Frequency
    unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    cuttoffFrequencyAttachment;
    juce::Label cutoffFrequencyLabel;
    
    juce::Slider qFactorSlider; ///Create a slider for the Q Factor
    unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    qFactorAttachment;
    juce::Label qFactorLabel;
    
    juce::Slider gainSlider; ///Create a slider for the EQ Gain
    unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    gainAttachment;
    juce::Label gainLabel;
    
    juce::Slider volumeSlider; ///Create a slider for the Q Factor
    unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>
    volumeAttachment;
    juce::Label volumeLabel;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BW_FilterTaskAudioProcessorEditor)
};
