/**
 * @file synth.cpp
 */
#include "synth.h"

/// <summary>
/// 
/// </summary>
/// <param name="channel"></param>
/// <returns></returns>
float Synth::signalProcess(int channel)
{
    float val = voicectrl_.signalProcess();

    return val;
}
