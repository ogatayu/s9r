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

/// <summary>
/// onNote
/// </summary>
/// <param name="nn">Note Num</param>
/// <param name="v">Velocity</param>
void Synth::onNote(int nn, int v)
{
    voicectrl_.onNote(nn, v);
}

/// <summary>
/// offNote
/// </summary>
/// <param name="nn">Note Num</param>
void Synth::offNote(int nn)
{
    voicectrl_.offNote(nn);
}
