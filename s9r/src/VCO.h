#pragma once

#include <stdint.h>
#include "ofMain.h"

class VCO {
public:
    VCO()
    {
        wave_phase_  = 0;
        nn_          = 0;
        current_nn_  = 0;
        detune_cent_ = 0;
    }
    ~VCO() {}

    // variable
    float wave_phase_;
    int   nn_;           // ���U�w�肳�ꂽ�m�[�gNo
    int   current_nn_;   // ���ݔ��U���̃m�[�gNo
    int   detune_cent_;  // �{�C�X�ԃf�`���[���l�i�P�ʂ̓Z���g�j

    /// <summary>
    /// setNoteNo
    /// </summary>
    /// <param name="nn"></param>
    /// <param name="is_key_on"></param>
    void  setNoteNo(int nn, bool is_key_on)
    {

    }

    /// <summary>
    /// calc
    /// </summary>
    /// <returns></returns>
    float calc()
    {
        float sample = sin(wave_phase_) * 0.3;

        float wave_phase_step = (440.0 / 44100.0) * TWO_PI;
        wave_phase_ += wave_phase_step;

        return sample;
    }
};
