#pragma once

#include <stdint.h>
#include "ofMain.h"
#include "ofLog.h"

class VCO {
public:
    VCO()
    {
        wave_phase_  = 0;
        nn_          = 0;
        current_nn_  = 0;
        detune_cent_ = 0;

        porta_start_nn_     = 0;
        current_porta_time_ = 0;
        porta_time_delta_   = 0;
        detune_cent_        = 0;
    }
    ~VCO() {}

    // variable
    float wave_phase_;
    int   nn_;           // ���U�w�肳�ꂽ�m�[�gNo
    int   current_nn_;   // ���ݔ��U���̃m�[�gNo
    int   detune_cent_;  // �{�C�X�ԃf�`���[���l�i�P�ʂ̓Z���g�j

    float  porta_start_nn_;     // �|���^�����g�J�n����noteNo
    float  current_porta_time_; // �|���^�����g�o�ߎ��ԁi1�Ő��K���A0�`1�Ń|���^�����g���j
    float  porta_time_delta_;   // �|���^�����g���x

    /**
     * @brief setNoteNo
     * @param nn 
     * @param is_key_on 
    */
    void  setNoteNo(int nn, bool is_key_on)
    {
        if (current_porta_time_ < 1.f) porta_start_nn_ = current_nn_;
        else                           porta_start_nn_ = nn_;

        if ((porta_start_nn_   != nn) &&
            (porta_time_delta_ != 0.f) &&
             is_key_on
             ) {

            // Start portamento
            current_porta_time_ = 0.f;
        }
        else {
            // Disable portamento
            current_porta_time_ = 1.f;
        }

        nn_ = nn;

        freq_ = 440.f * pow(2.f, (nn_ - 69.f) / 12.f);
        wave_phase_step_ = (freq_ / 44100.0) * TWO_PI;
        ofLogVerbose("VCO") << "Phase step: " << wave_phase_step_;
    }

    float freq_;
    float wave_phase_step_;

    /**
     * @brief  calc
     * @return 
    */
    float calc()
    { 
        float sample = sin(wave_phase_) * 0.5;
        wave_phase_ += wave_phase_step_;
        if (wave_phase_ >= TWO_PI) {
            wave_phase_ = wave_phase_ - TWO_PI;
        }

        return sample;
    }
};
