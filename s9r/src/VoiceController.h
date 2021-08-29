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
    std::list<Voice*> on_voices_;  // �L�[�I�����̃{�C�X���X�g
    
    // sound parameter
    int unison_num_;      // ���j�]���{�C�X��
    int poly_voice_num_;  // �|�����[�h���̍ő�{�C�X��
    
    // note controll variable
    int  on_key_num_;           // �������̃L�[��
    int  key_table_[128];       // �L�[�ƃx���V�e�B�Ƃ̑Ή��\
    int  on_key_nn_list_[128];  // �������ꂽ�L�[�̏��Ԃ�ێ����郊�X�g
    bool dumper_;               // �_���p�[�y�_���t���O
    bool dumper_table_[128];    // �_���p�[�I�t�ŁA�����[�X���ׂ����Տ��
    bool is_status_changed_;    // �L�[�̉�����Ԃ��ύX���ꂽ���̃t���O

    void triggerPoly();

    bool isStatusChanged() { return is_status_changed_; }
    void resetStatusChange();

    int current_voice_no_;
    Voice* getNextOffVoice();

    // n�ԖڂɐV���������L�[�̃m�[�gNO���擾�B�Ȃ���΁A-1��Ԃ��B
    int GetOnKeyNN(int n)
    {
        if (n >= on_key_num_) return -1;
        return on_key_nn_list_[on_key_num_ - 1 - n];
    };

    // n�ԖڂɐV�����V�K�����L�[�̃m�[�gNO���擾�B�Ȃ���΁A-1��Ԃ��B
    int getNewOnKeyNN(int n)
    {
        if (n >= on_key_num_) return -1;
        int note_num = on_key_nn_list_[on_key_num_ - 1 - n];
        if (note_num < 256) return -1;		// �V�K�ł͂Ȃ�
        return note_num - 256;
    };
};
