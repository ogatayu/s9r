/**
 * @file Envelope.h
 */
#pragma once

 /**
  * @class Envelope
  */
class Envelope {
public:
    Envelope();
    ~Envelope() {}

    void setup(float fs);

    float process(float in);

    void trigger();
    void release();

    void setAttack(int attack_ms);
    void setDecay(int decay_ms);
    void setSustain(float sustain_lv);
    void setRelease(int release_ms);

    bool isPlaying();

private:
    enum State
    {
        IDLE,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE
    };

    const int DECIMAL_BIT = 16;
    inline unsigned int toFixedPoint(float val)
    {
        return (unsigned int)((1 << DECIMAL_BIT) * val);
    }

    float fs_;  // sample rate

    enum State   state_;
    unsigned int count_;

    // 計算用の値16:16の固定小数点変数
    unsigned int fxp_out_lv_prev_;
    unsigned int fxp_sustain_lv_;

    int   attack_ms_;
    int   decay_ms_;
    float sustain_lv_;
    int   release_ms_;
    float release_lv_;

    void setState(enum State state);
};
