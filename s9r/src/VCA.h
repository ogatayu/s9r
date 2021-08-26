#pragma once

class VCA {
private:

public:
    VCA() {}
    ~VCA() {}
    void  trigger() {}
    void  release() {}
    bool  isPlaying() { return false; }

    float calc(float val)
    { 
        return val;
    }
};