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

private:
    const float tuning_ = 440.0f;

    VoiceController voicectrl_;
};

