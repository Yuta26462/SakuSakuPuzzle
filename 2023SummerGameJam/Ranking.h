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

public:
    struct RankingData
    {
        int no;
        char name[11];
        long score;
    };

    int ReadRanking(void);
    
    //コンストラクタ
    Ranking();

    //デストラクタ
    ~Ranking();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};