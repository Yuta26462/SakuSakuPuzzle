#pragma once
#include"AbstractScene.h"
#include "BlockManager.h"
#include "Bomb.h"
#include "Cursor.h"

class GameMain :
    public AbstractScene
{
private:
    BlockManager* block_manager;
    Bomb* bomb;
    Cursor* cursor;

    //�x���A�j���[�V�����p�J�E���^
    int delay_animation_count;

    enum class DELAY_ANIMATION_TYPE
    {
        FADE_IN,
        FADE_OUT,
        DELAY_ANIMATION_TYPE_SIZE
    };


public:

    //�R���X�g���N�^
    GameMain();

    //�f�X�g���N�^
    ~GameMain();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;


    //�`�悷��u���b�N�̊m�F

    void CheckBlock();

        /// <summary>
    /// �V�[���֑ؑO�̒x���A�j���[�V����
    /// </summary>
    /// <returns></returns>
    /// <remarks>�V�[���֑ؑO�ɒx���A�j���[�V�������s��</remarks>
    bool DelayAnimation(DELAY_ANIMATION_TYPE type, float time);
};