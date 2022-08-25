/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BW_FilterTaskAudioProcessorEditor::BW_FilterTaskAudioProcessorEditor(BW_FilterTaskAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    ///Create GUI Objects for Plugin Parameters
    ///Cutoff Frequency Dial GUI
    addAndMakeVisible(cutoffFrequencySlider); ///Add the Slider to the GUI
    cutoffFrequencySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); ///Set style to rotary dial
    cuttoffFrequencyAttachment.reset(
     new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "cutoff_frequency", cutoffFrequencySlider)); ///Attach the GUI Slider to the control of the cutoff frequency variable)
    addAndMakeVisible(cutoffFrequencyLabel); ///Add label to parameter
    cutoffFrequencyLabel.setText("Cutoff", juce::dontSendNotification); ///Set text of label and do not send notification
    
    ///Q Factor Dial GUI
    addAndMakeVisible(qFactorSlider); ///Add slider to the GUI
    qFactorSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); ///Set style to rotary dial
    qFactorAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "qFactor", qFactorSlider)); ///Attach slider to GUI
    addAndMakeVisible(qFactorLabel); ///Add label to slider
    qFactorLabel.setText("Q Factor", juce::dontSendNotification); ///Set text and do not send notification

    ///GainDial GUI
    addAndMakeVisible(gainSlider); ///Add slider to the GUI
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); ///Set style to rotary dial
    gainAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "gain", gainSlider)); ///Attach button to GUI
    addAndMakeVisible(gainLabel); ///Add label to slider
    gainLabel.setText("EQ Gain", juce::dontSendNotification); ///Set text and do not send notification
    
    ///Volume Dial GUI
    addAndMakeVisible(volumeSlider); ///Add slider to the GUI
    volumeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag); ///Set style to rotary dial
    volumeAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(vts, "volume", volumeSlider)); ///Attach slider to GUI
    addAndMakeVisible(volumeLabel); ///Add label to slider
    volumeLabel.setText("Output", juce::dontSendNotification); ///Set text and do not send notification
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (350, 200);
}

BW_FilterTaskAudioProcessorEditor::~BW_FilterTaskAudioProcessorEditor()
{
}

//==============================================================================
void BW_FilterTaskAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightgrey);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Issac Thomas - B&W Filter Challenge", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void BW_FilterTaskAudioProcessorEditor::resized()
{
    cutoffFrequencySlider.setBounds(10, 10, 100, 100);
    cutoffFrequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    cutoffFrequencyLabel.setBounds(cutoffFrequencySlider.getX() + 15, cutoffFrequencySlider.getY() + 100, 70, 30);

    qFactorSlider.setBounds(85, 10, 100, 100);
    qFactorSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    qFactorLabel.setBounds(qFactorSlider.getX() + 15, qFactorSlider.getY() + 100, 70, 30);
    
    gainSlider.setBounds(160, 10, 100, 100);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    gainLabel.setBounds(gainSlider.getX() + 15, gainSlider.getY() + 100, 70, 30);
    
    volumeSlider.setBounds(235, 10, 100, 100);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 70, 20);
    volumeLabel.setBounds(volumeSlider.getX() + 15, volumeSlider.getY() + 100, 70, 30);
    
    ///Design
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::black);
}

