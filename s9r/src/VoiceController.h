#pragma once

#include <list>
#include "voice.h"

/// <summary>
/// VoiceController
/// </summary>
class VoiceController {
public:
    VoiceController();
    ~VoiceController() {}

    float signalProcess();

private:
    static constexpr int VOICE_NUM = 32;

    Voice voice_[VOICE_NUM];
};
