#pragma once

#include <list>
#include "voice.h"

/// <summary>
/// VoiceController
/// </summary>
class VoiceController {
public:
    VoiceController();
    ~VoiceController() {}

    float signalProcess();

    void onNote(int nn, int v);
    void offNote(int nn);

private:
    static constexpr int VOICE_NUM = 32;

    Voice voice_[VOICE_NUM];
    std::list<Voice*> on_voices_;  // キーオン中のボイスリスト
    
    // sound parameter
    int unison_num_;      // ユニゾンボイス数
    int poly_voice_num_;  // ポリモード時の最大ボイス数
    
    // note controll variable
    int  on_key_num_;           // 押下中のキー数
    int  key_table_[128];       // キーとベロシティとの対応表
    int  on_key_nn_list_[128];  // 押下されたキーの順番を保持するリスト
    bool dumper_;               // ダンパーペダルフラグ
    bool dumper_table_[128];    // ダンパーオフで、リリースすべき鍵盤情報
    bool is_status_changed_;    // キーの押下状態が変更されたかのフラグ

    void triggerPoly();

    bool isStatusChanged() { return is_status_changed_; }
    void resetStatusChange();

    int current_voice_no_;
    Voice* getNextOffVoice();

    // n番目に新しい押鍵キーのノートNOを取得。なければ、-1を返す。
    int GetOnKeyNN(int n)
    {
        if (n >= on_key_num_) return -1;
        return on_key_nn_list_[on_key_num_ - 1 - n];
    };

    // n番目に新しい新規押鍵キーのノートNOを取得。なければ、-1を返す。
    int getNewOnKeyNN(int n)
    {
        if (n >= on_key_num_) return -1;
        int note_num = on_key_nn_list_[on_key_num_ - 1 - n];
        if (note_num < 256) return -1;		// 新規ではない
        return note_num - 256;
    };
};
