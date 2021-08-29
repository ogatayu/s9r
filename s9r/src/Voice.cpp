/**
 * @file voice.cpp
 */
#include <cstdint>
#include <math.h>

#include "voice.h"


/// <summary>
/// �M��������
/// </summary>
/// <returns></returns>
float Voice::calc()
{
    float val;
    val = vco.calc();
    val = vcf.calc(val);
    val = vca.calc(val);
    return val;
}

/// <summary>
/// �L�[�I�������ǂ�����Ԃ�
/// </summary>
/// <returns></returns>
bool Voice::isKeyOn()
{
    return key_on_;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Voice::isPlaying()
{
    return vca.isPlaying();
}

/// <summary>
/// �g���K�[�ʒm
/// </summary>
/// <param name=""></param>
void Voice::trigger(void)
{
    vca.trigger();
    key_on_ = true;
}

/// <summary>
/// �L�[�I�t�ʒm
/// </summary>
/// <param name=""></param>
void Voice::release(void)
{
    vca.release();
    key_on_ = false;
}


/// <summary>
/// ���U�m�[�gNo���̐ݒ�B�L�[�I�����ɃR�[�������B
/// </summary>
/// <param name="nn"></param>
/// <param name="velo"></param>
void Voice::setNoteParam(int nn, int velo)
{
    nn_ = nn;
    velocity_ = velo;
    vco.setNoteNo(nn, isKeyOn());
}

/// <summary>
/// ���j�]���ݒ�
/// </summary>
/// <param name="master_voice_ptr"></param>
/// <param name="unison_num"></param>
/// <param name="unison_no"></param>
void Voice::setUnisonParam(Voice* master_voice_ptr, int unison_num, int unison_no)
{
    /* do nothing (now...) */
}

