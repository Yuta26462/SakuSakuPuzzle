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

    // 選択しているメニュー
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
    // デバックメニュー選択用フラグ
    bool is_select_debug;
#endif // TITLE_DEBUG

    // フォントハンドル
    int menu_font;

    //選択SE用サウンドハンドル
    int select_se;
    //決定SE用サウンドハンドル
    int decision_se;

    //操作間隔時間
    int input_margin;

    //フェード用カウンタ
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

    //コンストラクタ
    Ranking();
    
    //デストラクタ
    ~Ranking();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};