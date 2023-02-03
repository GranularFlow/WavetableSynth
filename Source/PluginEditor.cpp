/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularFlowWavetableAudioProcessorEditor::GranularFlowWavetableAudioProcessorEditor (GranularFlowWavetableAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(audioProcessor.wavetableSynth);
    setSize (W_WIDTH, W_HEIGHT);
}

GranularFlowWavetableAudioProcessorEditor::~GranularFlowWavetableAudioProcessorEditor()
{
}

//==============================================================================
void GranularFlowWavetableAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void GranularFlowWavetableAudioProcessorEditor::resized()
{
    audioProcessor.wavetableSynth.setBounds(getLocalBounds());
}
