/**
 * @file synth.h
 */
#pragma once

#include <vector>

#include "VoiceController.h"


/// <summary>
/// Synth class
/// </summary>
class Synth {
public:
    Synth() {}
    ~Synth() {}

    float signalProcess(int channel);

    void onNote(int nn, int v);
    void offNote(int nn);

private:
    const float tuning_ = 440.0f;

    VoiceController voicectrl_;
};

