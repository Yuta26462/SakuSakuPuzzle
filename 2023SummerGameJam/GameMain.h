#pragma once
#include"AbstractScene.h"
#include "BlockManager.h"
#include "Bomb.h"
#include "Cursor.h"
#include "Block.h"
#include <vector>

class GameMain :
    public AbstractScene
{
private:
    int ClearStage;
    Bomb* bomb;
    BlockManager* block_manager;
    Cursor* cursor;
    
    int stage_num;

    //遅延アニメーション用カウンタ
    int delay_animation_count;

    enum class DELAY_ANIMATION_TYPE
    {
        FADE_IN,
        FADE_OUT,
        DELAY_ANIMATION_TYPE_SIZE
    };

    int time_image;    //制限時間画像用
    int time_circle_image;    //制限時間画像用
    int TimeCount = 0;
    int Time = 0;
public:

    //コンストラクタ
    GameMain(int stage_num = 0);

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;


    //描画するブロックの確認

    void CheckBlock();
    void CreateBlock();

        /// <summary>
    /// シーン切替前の遅延アニメーション
    /// </summary>
    /// <returns></returns>
    /// <remarks>シーン切替前に遅延アニメーションを行う</remarks>
    bool DelayAnimation(DELAY_ANIMATION_TYPE type, float time);

    //リセット処理
    void Reset();
};