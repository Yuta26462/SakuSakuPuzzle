#pragma once
#include "AbstractScene.h"

// �^�C�g���Ƀf�o�b�N���j���[��ǉ�
//#define TITLE_DEBUG

class Title :
    public AbstractScene
{
private:

    enum class MENU
    {
        PLAY,
        HELP,
        EXIT,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "�Ղꂢ",
        "�ւ��",
        "���イ��傤"
    };

    // �I�����Ă��郁�j���[
    int select_menu;

    // �t�H���g�n���h��
    int menu_font;

    //�I��SE�p�T�E���h�n���h��
    int select_se;
    //����SE�p�T�E���h�n���h��
    int decision_se;

    //����Ԋu����
    int input_margin;

    //�t�F�[�h�p�J�E���^
    int fade_counter;

public:

    //�R���X�g���N�^
    Title();

    //�f�X�g���N�^
    ~Title() final;

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};