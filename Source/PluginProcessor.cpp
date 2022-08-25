/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace std;
//==============================================================================
BW_FilterTaskAudioProcessor::BW_FilterTaskAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
#endif
    ///Parameter Identifiers
    parameters(*this, nullptr, juce::Identifier("FilterPlugin"),
               {make_unique<juce::AudioParameterFloat>("cutoff_frequency", "Cutoff Frequency", juce::NormalisableRange{20.f,20000.f,0.1f,0.2f, false}, 500.f),
        make_unique<juce::AudioParameterFloat>("qFactor", "Q Factor", juce::NormalisableRange{0.5f,100.0f, 0.1f, 1.f, false},10.f),
        make_unique<juce::AudioParameterFloat>("gain", "Gain", juce::NormalisableRange{-18.f, 18.f, 0.1f, 1.f, false}, 0.f),
        make_unique<juce::AudioParameterFloat>("volume", "Volume",juce::NormalisableRange{ -24.f, 12.f, 0.1f, 1.f, false}, 0.f)})
    {
        cutoffFrequencyParameter = parameters.getRawParameterValue("cutoff_frequency");
        qFactorParameter = parameters.getRawParameterValue("qFactor");
        gainParameter = parameters.getRawParameterValue("gain");
        volumeParameter = parameters.getRawParameterValue("volume");
    }

BW_FilterTaskAudioProcessor::~BW_FilterTaskAudioProcessor()
{
}

//==============================================================================
const juce::String BW_FilterTaskAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BW_FilterTaskAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BW_FilterTaskAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BW_FilterTaskAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BW_FilterTaskAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BW_FilterTaskAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BW_FilterTaskAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BW_FilterTaskAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BW_FilterTaskAudioProcessor::getProgramName (int index)
{
    return {};
}

void BW_FilterTaskAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BW_FilterTaskAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    filter.setSampleRate(static_cast<unsigned int>(sampleRate));
    filter.volume.reset(sampleRate, 0.02f); 
}

void BW_FilterTaskAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BW_FilterTaskAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void BW_FilterTaskAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    const float cutoffFrequency = cutoffFrequencyParameter->load();
    const float qFactor = qFactorParameter ->load();
    const float gain = gainParameter -> load();
    const float volume = volumeParameter -> load();
    
    filter.setCutoff(cutoffFrequency);
    filter.setQ(qFactor);
    filter.setGain(gain);
    filter.setVolume(volume);
    
    filter.processBlock(buffer, midiMessages); ///Send buffer to filter process block
}

//==============================================================================
bool BW_FilterTaskAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BW_FilterTaskAudioProcessor::createEditor()
{
    return new BW_FilterTaskAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BW_FilterTaskAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BW_FilterTaskAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BW_FilterTaskAudioProcessor();
}
