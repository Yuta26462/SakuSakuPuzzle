#pragma once
#include "AbstractScene.h"
#include <string>

class END :
    public AbstractScene
{
private:

    //遅延アニメーション用カウンタ
    int delay_animation_count;

    enum class DELAY_ANIMATION_TYPE
    {
        FADE_IN,
        FADE_OUT,
        DELAY_ANIMATION_TYPE_SIZE
    };

    // 選択しているメニュー
    int select_menu;

    int menu_font1;
    int menu_font2;

    //選択SE用サウンドハンドル
    int select_se;
    //決定SE用サウンドハンドル
    int decision_se;

    //操作間隔時間
    int input_margin;

    int WaitTime = 0;

    int time = 0;

    int fade_counter[2];

    //int fade_counter;

    int watting_time;

    enum class STATE
        {
        START,
        MIDDLE,
        END
    } state;

    //アニメーション管理
   // int Bright = 0;			//フェードアウト(0で完全に暗転)
public:

    //コンストラクタ
    END();

    //デストラクタ
    ~END();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    /// <summary>
/// シーン切替前の遅延アニメーション
/// </summary>
/// <returns></returns>
/// <remarks>シーン切替前に遅延アニメーションを行う</remarks>
    bool DelayAnimation(DELAY_ANIMATION_TYPE type, float time);
};