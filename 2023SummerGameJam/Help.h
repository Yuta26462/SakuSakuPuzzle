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

    // フォントハンドル
    int menu_font;
    int normal_font;

    //選択SE用サウンドハンドル
    int select_se;

    //決定SE用サウンドハンドル
    int decision_se;

    //操作間隔時間
    int input_margin;

    //フェード用カウンタ
    int fade_counter;

    int WaitTime = 0;

    int gamepad_image;
    int star_image;
    int bomb_image;
public:

    //コンストラクタ
    Help();

    //デストラクタ
    ~Help();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};
