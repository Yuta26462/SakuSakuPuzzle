#pragma once
#include "AbstractScene.h"

#define RANKING_DATA  5
#define KEYBORA_XMARGIN			30
#define KEYBORA_YMARGIN			30
#define KEYBORA_X				100
#define KEYBORA_Y				260

class Ranking :
    public AbstractScene
{
private:

    enum class MENU
    {
        a,
        //OPTION,
        b,
        c,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "a",
        //"OPTION",
        "b",
        "c"
    };

    struct	RankingData {
        int no;
        char name[10];
        long score;
    };

    // �I�����Ă��郁�j���[
    int select_menu;

    //int MoziSelectW;
    //int MoziSelectH;

    //char MoziSmall;
    //char MoziBig;
    //char MoziNumber;

    //char MoziFrame;
    //char MoziWork;
   //  #define RANKING_DATA
   // struct RankingData		gRanking[RANKING_DATA];
#ifdef TITLE_DEBUG
    // �f�o�b�N���j���[�I��p�t���O
    bool is_select_debug;
#endif // TITLE_DEBUG

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

    int color;

    RankingData g_Ranking[RANKING_DATA];

    int input_i;

    char buf[10];

    int display;

    int selecterX;
    int selecterY;

    char input_char;

    int KeyBoard_XMrgin;

    int KeyBoard_X;

    int i_space;

    char KeyMap_Qwerty[3][12] = { "QWERTYUIOP","ASDFGHJKL", "ZXCVBNM" };
        
    int Uplow;

public:

    //�R���X�g���N�^
    Ranking();
    
    //�f�X�g���N�^
    ~Ranking();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};