#pragma once
#include "AbstractScene.h"

class Help :
    public AbstractScene
{
private:

    int page;
    int star_x;
    int star_y;
    int angle_x;
    int angle_y;

    // �t�H���g�n���h��
    int menu_font;
    int normal_font;

    //�I��SE�p�T�E���h�n���h��
    int select_se;

    //����SE�p�T�E���h�n���h��
    int decision_se;

    //����Ԋu����
    int input_margin;

    //�t�F�[�h�p�J�E���^
    int fade_counter;

    int WaitTime = 0;

    int gamepad_image;
    int star_image;
    int bomb_image;
public:

    //�R���X�g���N�^
    Help();

    //�f�X�g���N�^
    ~Help();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};
