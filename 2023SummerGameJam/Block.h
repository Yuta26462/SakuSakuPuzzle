#pragma once

//#include "BlockManager.h"
// ブロックのサイズ
const int BLOCK_SIZE = 90;

class Block
{   
private:

public:

    int x, y; // ブロックの位置
    int xp, yp; // ブロックの位置
    int shape; // ブロックの形状（0: 無し, 1: 正方形, 2: 三角形）
    int rotation; // ブロックの回転（0: 0度, 1: 90度, 2: 180度, 3: 270度）

    int mx, my;//移動用
    bool is_hold;   // 掴まれているフラグ
    bool is_empty;

    //int blockimg[6];



public:

    Block();
    
    //デストラクタ
    ~Block();

    void Draw(int blockimg[6]);
    void Drawp(int blockimg[6]);
    void Update();

    void flg(int Moveflg);//Aボタンが押されたか確認
    void Hit(int Hitblock);//Aボタンが押されたか確認

    void rotate();
    //{
    //   // rotation = (rotation + 1) % 4;
    //}
};

