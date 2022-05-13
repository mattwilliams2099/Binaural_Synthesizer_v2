/*
  ==============================================================================

    ILD.cpp
    Created: 21 Apr 2022 3:50:27pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "ILD.h"

ILDClass::ILDClass(float samplerate) : sampleRate(samplerate)
{
    loadAmplitudeDatabase();
    //bandPassFilter[0].setBandPassCo(3.0f, 0.5f);
    //bandPassFilter[1].setBandPassCo(700.0f, 1.5f);
    //bandPassFilter[2].setBandPassCo(4000.0f, 3.0f);
    //bandPassFilter[3].setBandPassCo(13500.0f, 3.0f);
    setFilterRes(1.0f);
}

float ILDClass::process(float sample, int channel)
{
    float output = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        if(i == 2 || i == 0)
            output += (-bandPassFilter[i].filterProcess(sample, channel) * amplitudes[amplitudeIndex][i][channel]);
        else
            output += (bandPassFilter[i].filterProcess(sample, channel) * amplitudes[amplitudeIndex][i][channel]);
    }
    return(output);
}

void ILDClass::setSampleRate(float newSampleRate)
{
    sampleRate = newSampleRate;
    for (FilterClass filter : bandPassFilter)
        filter.setSampleRate(newSampleRate);
    setFilterRes(filterRes);
}

void ILDClass::setFilterRes(float newFilterResonances)
{
    filterRes = newFilterResonances;
    bandPassFilter[0].setBandPassCo(3.0f, 0.5f * newFilterResonances);
    bandPassFilter[1].setBandPassCo(700.0f, 1.5f * newFilterResonances);
    bandPassFilter[2].setBandPassCo(4000.0f, 3.0f * newFilterResonances);
    bandPassFilter[3].setBandPassCo(13500.0f, 3.0f * newFilterResonances);
}

void ILDClass::loadAmplitudeDatabase()
{
   // juce::File resourceFile = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("test.txt");
        
       // getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getChildFile("source\\test.txt");
    //juce::File resourceFile2 = resourceFile.getParentDirectory();
    //juce::File resourceFile3 = resourceFile2.getParentDirectory();
    //juce::File myFile = resourceFile3.getChildFile("source\\lowBandAmplitudes_left.txt");
    //juce::File resourceFile = juce::File::getCurrentWorkingDirectory();
    //juce::String filePath = resourceFile3.getFullPathName();

   // juce::String test2 = resourceFile.loadFileAsString();
    
    
    //.getChildFile("lowBandAmplitudes_left.txt");

   // if (!resourceFile.existsAsFile())
   // {
     //   DBG("File doesn't exist ...");
    //}
    std::ifstream amplitudesFile[8];
    //amplitudesFile[0].open("C:\\Users\\Matthew Williams\\Documents\\JUCE Plugin Dev\\BinauralSynthesizer\\BinauralSynthesizer\\Source\\subBandAmplitudes_left.txt");
    //amplitudesFile[1].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/subBandAmplitudes_right.txt");
    //amplitudesFile[2].open("lowBandAmplitudes_left.txt");
    //amplitudesFile[3].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/lowBandAmplitudes_right.txt");
    //amplitudesFile[4].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_left.txt");
    //amplitudesFile[5].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_right.txt");
    //amplitudesFile[6].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_left.txt");
    //amplitudesFile[7].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_right.txt");
    std::string loc[8];
    loc[0] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\subBandAmplitudes_left.txt").getFullPathName().toStdString();
    loc[1] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\subBandAmplitudes_right.txt").getFullPathName().toStdString();
    loc[2] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\lowBandAmplitudes_left.txt").getFullPathName().toStdString();
    loc[3] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\lowBandAmplitudes_right.txt").getFullPathName().toStdString();
    loc[4] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\midBandAmplitudes_left.txt").getFullPathName().toStdString();
    loc[5] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\midBandAmplitudes_right.txt").getFullPathName().toStdString();
    loc[6] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\highBandAmplitudes_left.txt").getFullPathName().toStdString();
    loc[7] = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory).getChildFile("Binaural_Synthesizer_Resources\\highBandAmplitudes_right.txt").getFullPathName().toStdString();


    //amplitudesFile[0].open("C:\\Users\\Matthew Williams\\Documents\\JUCE Plugin Dev\\BinauralSynthesizer\\BinauralSynthesizer\\Source\\subBandAmplitudes_left.txt");
    //amplitudesFile[1].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/subBandAmplitudes_right.txt");
    //amplitudesFile[2].open("lowBandAmplitudes_left.txt");
    //amplitudesFile[3].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/lowBandAmplitudes_right.txt");
    //amplitudesFile[4].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_left.txt");
    //amplitudesFile[5].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/midBandAmplitudes_right.txt");
    //amplitudesFile[6].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_left.txt");
    //amplitudesFile[7].open("C:/Users/Matthew Williams/Documents/JUCE Plugin Dev/BinauralSynthesizer/BinauralSynthesizer/Source/highBandAmplitudes_right.txt");

    int m = 0;
    int t = 0;
    for (int i = 0; i < 8; i++)
    {
        amplitudesFile[i].open(loc[i]);
        int n = 0;
        if (amplitudesFile[i].is_open())
        {
            while (amplitudesFile[i] >> amplitudes[n][t][m])
            {
                n++;
            }
            amplitudesFile[i].close();
        }
        m++;
        if (m == 2)
        {
            t++;
            m = 0;
        }
    }
}