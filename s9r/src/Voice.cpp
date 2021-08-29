/**
 * @file voice.cpp
 */
#include <cstdint>
#include <math.h>

#include "voice.h"


/// <summary>
/// 信号処理部
/// </summary>
/// <returns></returns>
float Voice::calc()
{
    float val;
    val = vco.calc();
    val = vcf.calc(val);
    val = vca.calc(val);
    return val;
}

/// <summary>
/// キーオン中かどうかを返す
/// </summary>
/// <returns></returns>
bool Voice::isKeyOn()
{
    return key_on_;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Voice::isPlaying()
{
    return vca.isPlaying();
}

/// <summary>
/// トリガー通知
/// </summary>
/// <param name=""></param>
void Voice::trigger(void)
{
    vca.trigger();
    key_on_ = true;
}

/// <summary>
/// キーオフ通知
/// </summary>
/// <param name=""></param>
void Voice::release(void)
{
    vca.release();
    key_on_ = false;
}


/// <summary>
/// 発振ノートNo等の設定。キーオン毎にコールされる。
/// </summary>
/// <param name="nn"></param>
/// <param name="velo"></param>
void Voice::setNoteParam(int nn, int velo)
{
    nn_ = nn;
    velocity_ = velo;
    vco.setNoteNo(nn, isKeyOn());
}

/// <summary>
/// ユニゾン設定
/// </summary>
/// <param name="master_voice_ptr"></param>
/// <param name="unison_num"></param>
/// <param name="unison_no"></param>
void Voice::setUnisonParam(Voice* master_voice_ptr, int unison_num, int unison_no)
{
    /* do nothing (now...) */
}

