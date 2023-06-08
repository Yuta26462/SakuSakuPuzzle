#pragma once
#include "AbstractScene.h"

class Ranking :
    public AbstractScene
{
private:
  
    enum class MENU
    {
        PLAY,
        //OPTION,
        HELP,
        EXIT,
        MENU_SIZE
    };

    const char* menu_items[static_cast<int>(MENU::MENU_SIZE)] = {
        "PLAY",
        //"OPTION",
        "HELP",
        "EXIT"
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

public:
    struct RankingData
    {
        int no;
        char name[11];
        long score;
    };

    int ReadRanking(void);
    
    //�R���X�g���N�^
    Ranking();

    //�f�X�g���N�^
    ~Ranking();

    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;

    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};