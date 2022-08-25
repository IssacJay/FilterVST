//
//  AudioFilter.cpp
//  BW_FilterTask
//
//  Created by Issac  Jay on 23/07/2022.
//

#include "AudioFilter.hpp"
#include <math.h>

using namespace std;

///Scope resolution operators have been used to define the functions after declaration inside of the PeakFilter class
void PeakFilter::setCutoff(float cutoffFreq){
    this->cutoffFreq = cutoffFreq;
}

void PeakFilter::setQ(float qFactor){
    this->qFactor = qFactor;
}

void PeakFilter::setGain(float gain){
    this->gain = gain;
}

void PeakFilter::setVolume(float volume){
    this->volume = volume;
}

void PeakFilter::setSampleRate(unsigned int samplingRate){
    this->samplingRate = samplingRate;
}




//Filter Processing Block function
void PeakFilter::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&){

    ///Previous buffer values
    xn1Buffer.resize(buffer.getNumChannels(), 0.0); ///x[n-1]
    xn2Buffer.resize(buffer.getNumChannels(), 0.0); ///x[n-2]
    yn1Buffer.resize(buffer.getNumChannels(), 0.0); ///y[n-1]
    yn2Buffer.resize(buffer.getNumChannels(), 0.0); ///y[n-2]
    
    ///EQ Intermediate Variables
    float pi = M_PI; ///Pi = 3.14...
    float angFreq = 2 * pi * cutoffFreq/samplingRate; ///Angular frequency of critical frequency
    float alpha = (sin(angFreq))/2*qFactor; /// alpha value
    float A = powf(10.0, (gain/40.0)); ///A factor of difference equation
    
    ///Filter Coefficients
    float bCoef[3] = {1 + (alpha*A), -2*cos(angFreq), 1 - (alpha*A)}; ///b0 b1 b2 coefficients
    float aCoef[3] = {1 + (alpha/A), -2*cos(angFreq), 1 - (alpha/A)}; ///a0 a1 a2 coefficients
    
    ///Filter Processing Block
    ///Iterate through each audio channel
    for(auto channel = 0; channel < buffer.getNumChannels(); ++channel){
        float* channelSamples = buffer.getWritePointer(channel); ///Return pointer to the current audio channel
        
        for(unsigned int i = 0; i < buffer.getNumSamples(); ++i){ ///Iterate through samples in current buffer
            float inputSample = channelSamples[i]; ///Get sample from index inside current channel buffer
            
            ///Difference Equation of Peaking EQ
            float yn = ((bCoef[0]/aCoef[0])*inputSample) + ((bCoef[1]/aCoef[0])*xn1Buffer[channel]) + ((bCoef[2]/aCoef[0])*xn2Buffer[channel]) - ((aCoef[1]/aCoef[0])*yn1Buffer[channel]) - ((aCoef[2]/aCoef[0])*yn2Buffer[channel]);
            
            xn2Buffer[channel] = xn1Buffer[channel];
            xn1Buffer[channel] = inputSample;
            yn2Buffer[channel] = yn1Buffer[channel];
            yn1Buffer[channel] = yn;
            
            /*
            channelSamples[i] = yn * powf(10.0, (volume.getNextValue()/40.0)); /// getNextValue() should apply smoothing to volume parameter, however, audible clicks still appear in VST
             */
            
            ///Output
            channelSamples[i] = yn * powf(10.0, (volume.getNextValue()/40.0)); ///Assign filtered sample to output sample and apply volume
        }
    }
}
    
    
    
     
    
    

