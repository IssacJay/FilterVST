//
//  AudioFilter.hpp
//  BW_FilterTask
//
//  Created by Issac  Jay on 23/07/2022.
//
#include <vector>
#include "JuceHeader.h"

using namespace std;

class PeakFilter {
public:
    ///Function Declaration for EQ Processing
    //void setHighpass(bool highpass); ///To switch filter type from lowpass to highpass
    void setCutoff(float cutoffFreq); ///Set cutoff frquency function
    void setQ(float qFactor); ///Set Q Factor
    void setGain(float gain); ///Set filter Gain
    void setVolume(float volume); ///Set output volume
    void setSampleRate(unsigned int samplingRate); ///Set sampling rate
     
    juce::SmoothedValue<float> volume;
    
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&); ///Filter processing function
    
private:
    //bool highpass; //Bool to switch filter state
    float cutoffFreq; ///Critical Frequency value
    float qFactor; ///Q Factor
    float gain; ///Filter Gain
    //float volume; ///Master volume
    unsigned int samplingRate; ///Positive integer sampling rate
    
    vector<float> xn1Buffer; ///Store value v[n]
    vector<float> xn2Buffer; ///Store value v[n-1]
    vector<float> yn1Buffer; ///Store value v[n-2]
    vector<float> yn2Buffer; ///Store value y[n]
    
};

