#pragma once
#include "AbstractScene.h"

// タイトルにデバックメニューを追加
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
        "ぷれい",
        "へるぷ",
        "しゅうりょう"
    };

    // 選択しているメニュー
    int select_menu;

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

    //コンストラクタ
    Title();

    //デストラクタ
    ~Title() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};