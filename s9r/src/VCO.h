#pragma once

#include <stdint.h>

class VCO {
public:
    VCO()
    {
        phase_       = 0;
        nn_          = 0;
        current_nn_  = 0;
        detune_cent_ = 0;
    }
    ~VCO() {}

    // variable
    uint32_t phase_;        // 16:16 fixed-point
    int      nn_;           // ���U�w�肳�ꂽ�m�[�gNo
    int      current_nn_;   // ���ݔ��U���̃m�[�gNo
    int      detune_cent_;  // �{�C�X�ԃf�`���[���l�i�P�ʂ̓Z���g�j

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
        return 0.0f;
    }
};
