/**
 * @file VoiceController.cpp
 */

#include "VoiceController.h"

/// <summary>
/// VoiceController constructor
/// </summary>
VoiceController::VoiceController()
{
    unison_num_     = 1;
    poly_voice_num_ = 16;  // 16 voices

    on_key_num_        = 0;
    dumper_            = false;
    is_status_changed_ = false;
    for (int ix = 0; ix < 128; ix++) {
        key_table_[ix]      = 0;
        on_key_nn_list_[ix] = 0;
        dumper_table_[ix]   = 0;
    }
    current_voice_no_ = 0;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float VoiceController::signalProcess()
{
    if (is_status_changed_) {
        triggerPoly();
        resetStatusChange();  // 鍵盤状態変更フラグを落とす
    }

    float val = 0;

#if 1
    for (int ix = 0; ix < VOICE_NUM; ix++) {
        if (voice_[ix].isPlaying() == true) {
            val += voice_[ix].calc();
        }
    }
#else
    val += voice_[0].calc();
#endif

	return val;
}


/**
 * @brief triggerPoly
*/
void VoiceController::triggerPoly()
{
    // ノートオフならリリースする
    for (std::list<Voice*>::iterator v = on_voices_.begin(); v != on_voices_.end(); ) {
        if (key_table_[(*v)->getNoteNo()] == 0) {
            (*v)->release();
            v = on_voices_.erase(v);
        }
        else {
            v++;
        }
    }

    // トリガー処理
    int num = MIN(poly_voice_num_, on_key_num_);
    for (int i = 0; i < num; i++) {

        int noteNo = getNewOnKeyNN(i);
        if (noteNo == -1) break;

        // 同じノート番号のボイスがあればリリースする
        for (std::list<Voice*>::iterator v = on_voices_.begin(); v != on_voices_.end(); ) {
            if ((*v)->getNoteNo() == noteNo) {
                (*v)->release();
                v = on_voices_.erase(v);
            }
            else v++;
        }

        // ユニゾンボイスの数だけトリガー処理
        Voice* pUnisonMasterVoice;
        for (int u = 0; u < unison_num_; u++) {
            Voice* v = getNextOffVoice();
            if (v == NULL) {
                v = on_voices_.front();
                if (v == NULL) return;
                on_voices_.pop_front();
            }
            current_voice_no_ = v->getNo();
            if (u == 0) pUnisonMasterVoice = v;

            v->setNoteParam(noteNo, key_table_[noteNo]);
            v->setUnisonParam(pUnisonMasterVoice, unison_num_, u);
            v->trigger();

            on_voices_.push_back(v);
        }
    }
}

/**
 * @brief 使用されていないVoiceを検索して返す
 */
Voice* VoiceController::getNextOffVoice()
{
    int current_voice_no = current_voice_no_;
    for (int i = 0; i < VOICE_NUM; i++) {
        current_voice_no = (current_voice_no + 1) % VOICE_NUM;
        if (!voice_[current_voice_no].isPlaying()) {
            return &(voice_[current_voice_no]);
        }
    }

    // どれもオンだった
    return nullptr;
}

/**
 * @brief onNote
 * @param nn Note Num
 * @param v  Velocity
*/
void VoiceController::onNote(int nn, int v)
{
    if (key_table_[nn] != 0) { offNote(nn); }

    key_table_[nn]               = v;
    dumper_table_[nn]            = false;
    on_key_nn_list_[on_key_num_] = nn + 256;  // +256は新規押鍵フラグ
    on_key_num_++;

    is_status_changed_ = true;
}

/**
 * @brief offNote
 * @param nn Note Num
*/
void VoiceController::offNote(int nn)
{
    key_table_[nn]     = 0;
    is_status_changed_ = true;

    // オンキーリストから、キーオフした鍵盤情報を取り除く
    for (int i = 0; i < on_key_num_; i++) {
        int on_nn = on_key_nn_list_[i];
        if (nn == ((on_nn >= 256) ? on_nn - 256 : on_nn)) {
            for (; i < on_key_num_ - 1; i++) {
                on_key_nn_list_[i] = on_key_nn_list_[i + 1];
            }
            on_key_num_--;
            return;
        }
    }
}

/**
 * @brief resetStatusChange
*/
void VoiceController::resetStatusChange()
{
    is_status_changed_ = false;

    // 新規押鍵フラグもすべて落とす
    for (int i = 0; i < on_key_num_; i++) {
        if (on_key_nn_list_[i] >= 256) {
            on_key_nn_list_[i] -= 256;
        }
    }
}