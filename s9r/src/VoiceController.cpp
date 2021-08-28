/**
 * @file VoiceController.cpp
 */

#include "VoiceController.h"

/// <summary>
/// VoiceController constructor
/// </summary>
VoiceController::VoiceController()
{

}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float VoiceController::signalProcess()
{
    float   val = 0;

#if 0
    for (int ix = 0; ix < VOICE_NUM; ix++) {
        if (voice_[ix].isPlaying() == true) {
            val += voice_[ix].calc();
        }
    }
#endif
    val += voice_[0].calc();

	return val;
}
