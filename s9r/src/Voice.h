#pragma once

#include "VCO.h"
#include "VCF.h"
#include "VCA.h"

/// <summary>
/// Voice class
/// </summary>
class Voice {
private:
public:
    Voice() {
        voice_no_ = 0;
        nn_       = 0;
        velocity_ = 0;
        key_on_   = false;
    }
    ~Voice() {}

    VCO vco;
    VCF vcf;
    VCA vca;

    int  voice_no_;  // Voice No.
    int  nn_;        // Note No.
    int  velocity_;  // velocity when key on
    bool key_on_;    // if key on then true


    float calc();
    void  trigger();
    void  release();

    void setNo(int no) { voice_no_ = no; };    // ボイス番号を設定
    int  getNo()       { return voice_no_; };  // ボイス番号を返す

    void setNoteParam(int nn, int velo);
    int  getNoteNo() { return nn_; };    // 発振ノートNoを返す
    void setUnisonParam(Voice& pMasterVoice, int unisonNum, int unisonNo);

    bool  isPlaying();
    bool  isKeyOn();
};
