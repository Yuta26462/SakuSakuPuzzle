#pragma once
#include"AbstractScene.h"
#include "BlockManager.h"
#include "Bomb.h"
#include "Cursor.h"

class GameMain :
    public AbstractScene
{
private:
    BlockManager* block_manager;
    Bomb* bomb;
    Cursor* cursor;

    //遅延アニメーション用カウンタ
    int delay_animation_count;

    enum class DELAY_ANIMATION_TYPE
    {
        FADE_IN,
        FADE_OUT,
        DELAY_ANIMATION_TYPE_SIZE
    };


public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;


    //描画するブロックの確認

    void CheckBlock();

        /// <summary>
    /// シーン切替前の遅延アニメーション
    /// </summary>
    /// <returns></returns>
    /// <remarks>シーン切替前に遅延アニメーションを行う</remarks>
    bool DelayAnimation(DELAY_ANIMATION_TYPE type, float time);
};