#pragma once

#include "Envelope.h"

class VCA {
public:
    VCA()
    {
        env_.setup(44100);
        env_.setAttack(10);
        env_.setDecay(100);
        env_.setSustain(0.5f);
        env_.setRelease(1000);
    }
    ~VCA() {}

    void  trigger()
    {
        env_.trigger();
    }
    
    void  release()   { env_.release();}
    bool  isPlaying() { return env_.isPlaying(); }

    float calc(float val) { return env_.process(val) * 0.5f; }

private:
    Envelope env_;
};
