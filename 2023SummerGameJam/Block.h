#pragma once
#include "Cursor.h"
//#include "BlockManager.h"
// ブロックのサイズ
const int BLOCK_SIZE = 90;

class Block
{
private:/*
    Cursor::POSITION cursor_pos;*/
    Cursor* cursor;

public:

    int x, y; // ブロックの位置
    int xp, yp; // ブロックの位置
    int shape; // ブロックの形状（0: 正方形, 1: 三角形）
    int rotation; // ブロックの回転（0: 0度, 1: 90度, 2: 180度, 3: 270度）

    int mx, my;//移動用
    //int cx, cy;//カーソルの位置

  // int MoveFlg=0;

    //int blockimg[6];




    int CompBlock[1][4][4] = { 0 };	//お手本、影ブロック用

    int PartsBlock[1][4][4] = { 0 };	//パーツのブロック用

    int MoveBlock[1][4][4] = { 0 };



public:

    Block() = default;
    //引数有りコンストラクタ
    Block(Cursor * cursor);
    //デストラクタ
    ~Block();

    void Draw();
    void Drawp();
    void Mx(int& x);
    void My(int& y);/*
    void Getc(Cursor::POSITION* cursor);*/
    void Update();

    void flg(int Moveflg);

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

