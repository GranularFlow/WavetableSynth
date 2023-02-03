/*
  ==============================================================================

    WavetableSynth.cpp
    Created: 3 Feb 2023 12:45:49pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableSynth.h"


WavetableSynth::WavetableSynth()
{
    addAndMakeVisible(canvas1);
    addAndMakeVisible(canvas2);
    addAndMakeVisible(canvas3);

    addAndMakeVisible(wavetableSettings);
}

WavetableSynth::~WavetableSynth()
{
}

void WavetableSynth::paint(Graphics& g)
{
    g.fillAll(C_DARK);
    paintLogoOnce(g);

}


void WavetableSynth::paintLogoOnce(Graphics& g)
{
    const Image logo = ImageFileFormat::loadFrom(BinaryData::logo250_png, BinaryData::logo250_pngSize);
    g.drawImageAt(logo, (50 - 36) / 2, 7, false);

}

void WavetableSynth::resized()
{
    canvas1.setBounds(getLocalBounds().withTrimmedLeft(50).withTrimmedTop(100).withTrimmedBottom(getHeight()/ 2).withTrimmedRight((W_WIDTH * 2/3) + 50));
    canvas2.setBounds(getLocalBounds().withTrimmedLeft(50 + (W_WIDTH * 1 / 3)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight((W_WIDTH * 1 / 3) + 50));
    canvas3.setBounds(getLocalBounds().withTrimmedLeft(50 + (W_WIDTH * 2 / 3)).withTrimmedTop(100).withTrimmedBottom(getHeight() / 2).withTrimmedRight(50));
    
    wavetableSettings.setBounds(getLocalBounds()
        .withTrimmedTop((getHeight()* 2/3) * 1.01)
        .withTrimmedLeft(getWidth() * 0.01)
        .withTrimmedRight(getWidth() * 0.01)
        .withTrimmedBottom(getWidth() * 0.01)
    );
}

void WavetableSynth::initSamples()
{
    // samples from canvas1 to canvas2
    // canvas 1 samples
    for (int i = 0; i < canvas1.waveTableSamples.size(); i++)
    {
        sampleY.add(canvas1.waveTableSamples[i]);
        sampleX.add(canvas1.xPos[i]);
    }

    int semitotalSamples = (wavetableSettings.getWaveCount() / 2) * 100;


    for (int i = 0; i < semitotalSamples; i++)
    {
        //y1 + (x - x1) * (y2 - y1) / (x2 - x1)
        //(float x, float x1, float y1, float x2, float y2)
        /*float y = sampleY.getLast() + ((sampleX.getLast() + 3) - sampleX.getLast()) * (canvas2 - sampleY.getLast()) / (x2 - sampleX.getLast())
        sampleY.add(y);/*
    }
}

void WavetableSynth::getNextBlock(AudioBuffer<float>& bufferToFill, MidiBuffer& midiMessages)
{
    float* leftChannel = bufferToFill.getWritePointer(0);
    float* rightChannel = bufferToFill.getWritePointer(1);

    if (wavetableSettings.isCurrentMidiMode(WavetableSynthSettings::MidiMode::ON))
    {
        handleMidi(midiMessages);
        if (midiNoteOn) {
            float totalPosition = fmod((currentPosition * increment), sampleY.size());
        }
    }
    else
    {
       
    }

}

void WavetableSynth::handleMidi(MidiBuffer& midiMessages)
{
    MidiBuffer::Iterator iter(midiMessages);
    MidiMessage midiMsg;
    int midiPos;
    iter.getNextEvent(midiMsg, midiPos);
    if (midiMsg.isNoteOn() && midiMsg.getNoteNumber() != lastMidiNote)
    {
        midiNoteOn = true;
        lastMidiNote = midiMsg.getNoteNumber();
        increment = std::powf(2.f, (midiMsg.getNoteNumber() - 69.f) / 12.f);
    }
    else if (midiMsg.isNoteOff() && midiMsg.getNoteNumber() == lastMidiNote)
    {
        midiNoteOn = false;
        lastMidiNote = -1;
        increment = 1.0f;
    }
}