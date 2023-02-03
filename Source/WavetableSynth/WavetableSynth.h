/*
  ==============================================================================

    WavetableSynth.h
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Constants.h"
#include "WavetableSynthSettings/WavetableSynthSettings.h"
#include "Canvas/Canvas.h"
class WavetableSynth : public Component
{
public:
    // Class
	WavetableSynth();
	~WavetableSynth();
    // GUI
    void paint(Graphics&) override;
    void paintLogoOnce(Graphics&);
    void resized()override;

    /*
    // Listeners
    void sliderValueChanged(Slider*) override;
    void addListeners();
    void removeListeners();
    // Process
    void prepareToPlay(double, int);
    void getNextBlock(AudioBuffer<float>&, juce::MidiBuffer&);
    */
    void initSamples();
    void interpolate();
    void interpolateLinear();
    void getNextBlock(AudioBuffer<float>& ,MidiBuffer& midiMessages);
    void handleMidi(MidiBuffer&);
private:
    Canvas canvas1;
    Canvas canvas2;
    Canvas canvas3;
    WavetableSynthSettings wavetableSettings;
    Array<float> sampleY;
    Array<float> sampleX;

    bool midiNoteOn = false;
    int lastMidiNote = -1;
    int midiNoteFrequency = 0;
    int currentPosition = 0;
    float increment = 1.0;
};
