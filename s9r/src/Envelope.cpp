/**
 * @file envelope.cpp
 */
#include <cstdio>

#include "envelope.h"


 /**
  * @brief constructor
  */
Envelope::Envelope()
{

    setAttack(1);
    setDecay(1);
    setSustain(1.f);
    setRelease(1);

    fs_              = 0;
    state_           = IDLE;
    fxp_out_lv_prev_ = 0;
    release_lv_      = 0;
    count_           = 0;
}

/// <summary>
/// setup
/// </summary>
/// <param name="fs">samplerate</param>
void Envelope::setup(float fs)
{
    fs_ = fs;
}

/**
 * @brief process
 */
float Envelope::process(float in)
{
    count_++;
    unsigned int fxp_elapsed_ms = toFixedPoint((count_ * 1000) / fs_);

    int fxp_out_lv;
    switch (state_)
    {
    case IDLE:
        fxp_out_lv = 0;
        break;

    case ATTACK:
        fxp_out_lv = fxp_elapsed_ms / attack_ms_;

        if (fxp_elapsed_ms >= toFixedPoint(attack_ms_)) {
            setState(DECAY);
        }
        break;

    case DECAY:
        fxp_out_lv = (1 << DECIMAL_BIT) - ((1.0f - sustain_lv_) * (fxp_elapsed_ms / decay_ms_));

        if (fxp_elapsed_ms >= toFixedPoint(decay_ms_)) {
            setState(SUSTAIN);
        }
        break;

    case SUSTAIN:
        fxp_out_lv = fxp_sustain_lv_;
        break;

    case RELEASE:
        fxp_out_lv = toFixedPoint(release_lv_) - (release_lv_ * (fxp_elapsed_ms / release_ms_));

        if (fxp_elapsed_ms >= toFixedPoint(release_ms_)) {
            setState(IDLE);
        }
        break;

    default:
        fxp_out_lv = 0;
        break;
    }

    // limiter
    fxp_out_lv = (fxp_out_lv > (1 << DECIMAL_BIT)) ? (1 << DECIMAL_BIT) : ((fxp_out_lv < 0) ? 0 : fxp_out_lv);

    fxp_out_lv_prev_ = fxp_out_lv;
    return (float)(in * fxp_out_lv) / (float)(1 << DECIMAL_BIT);
}

/**
 * @brief trigger
 */
void Envelope::trigger()
{
    fxp_out_lv_prev_ = 0;
    setState(ATTACK);
}

/**
 * @brief release
 */
void Envelope::release()
{
    release_lv_ = (float)fxp_out_lv_prev_ / (1 << DECIMAL_BIT);
    setState(RELEASE);
}

/**
 * @brief SetAttack
 *
 * @note Atatck time‚Í1[ms]ˆÈã‚ðŽw’è‚·‚é‚±‚Æ
 *
 * @param[in] attack_ms
 */
void Envelope::setAttack(int attack_ms)
{
    attack_ms_ = attack_ms;
}

/**
 * @brief setDecay
 */
void Envelope::setDecay(int decay_ms)
{
    decay_ms_ = decay_ms;
}

/**
 * @brief setSustain
 */
void Envelope::setSustain(float sustain_lv)
{
    sustain_lv_     = sustain_lv;
    fxp_sustain_lv_ = toFixedPoint(sustain_lv);
}

/**
 * @brief setRelease
 */
void Envelope::setRelease(int release_ms)
{
    release_ms_ = release_ms;
}

/**
 * @brief isPlaying
 */
bool Envelope::isPlaying()
{
    return (state_ != IDLE);
}

/**
 * @brief setState
 */
void Envelope::setState(enum State state)
{
    state_ = state;
    count_ = 0;
}
