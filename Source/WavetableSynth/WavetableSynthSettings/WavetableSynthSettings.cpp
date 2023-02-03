/*
  ==============================================================================

    WavetableSynthSettings.cpp
    Created: 3 Feb 2023 12:46:01pm
    Author:  honza

  ==============================================================================
*/

#include "WavetableSynthSettings.h"


WavetableSynthSettings::WavetableSynthSettings()
{
    addAndMakeVisible(midiModeRadioBox);
    addAndMakeVisible(freqKnob);
    addAndMakeVisible(waveCountKnob);
    addAndMakeVisible(volumeKnob);
    addAndMakeVisible(interpolationRadioBox);
    addAndMakeVisible(panKnob);
}

WavetableSynthSettings::~WavetableSynthSettings()
{
}

void WavetableSynthSettings::paint(Graphics& g)
{
    g.setColour(L_GRAY);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), 30);
}

void WavetableSynthSettings::resized()
{
    int sectionWidth = (getWidth() * 0.9) / 6;
    int sectionHeight = getHeight();

    FlexBox fb{
            FlexBox::Direction::row,
            FlexBox::Wrap::noWrap,
            FlexBox::AlignContent::center,
            FlexBox::AlignItems::flexStart,
            FlexBox::JustifyContent::spaceAround
    };

    // Second column
    int tmp_height = sectionHeight;
    int tmp_width = 100;
    fb.items.add(FlexItem(midiModeRadioBox).withOrder(1).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(freqKnob).withOrder(3).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(waveCountKnob).withOrder(5).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(interpolationRadioBox).withOrder(5).withMinWidth(tmp_width).withMinHeight(tmp_height));
    fb.items.add(FlexItem(volumeKnob).withOrder(9).withMinWidth(tmp_width).withHeight(tmp_height));
    fb.items.add(FlexItem(panKnob).withOrder(11).withMinWidth(tmp_width).withHeight(tmp_height));


    // White lines
    for (int8 i = 0; i < 6; i++)
    {
        fb.items.add(FlexItem(*separators[i]).withMinWidth(1).withHeight(sectionHeight).withOrder((i + 1) * 2));
    }

    fb.performLayout(getLocalBounds());

}


float WavetableSynthSettings::getFreq()
{
    return freqKnob.getValue();
}

float WavetableSynthSettings::getWaveCount()
{
    return 0.0f;
}

float WavetableSynthSettings::getVolume()
{
    return (float)volumeKnob.getValue() / 100;
}

float WavetableSynthSettings::getPan(int8 channel)
{
    return  1 - abs(channel - ((float)panKnob.getValue() / 100));
}

bool WavetableSynthSettings::isCurrentMidiMode(WavetableSynthSettings::MidiMode mode)
{
    return ((WavetableSynthSettings::MidiMode)midiModeRadioBox.getValue() == mode);
}

bool WavetableSynthSettings::isCurrentInterpolationType(WavetableSynthSettings::InterpolationType type)
{
    return ((WavetableSynthSettings::InterpolationType)interpolationRadioBox.getValue() == type);
}
