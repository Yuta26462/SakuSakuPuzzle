#pragma once

// ブロックのサイズ
const int BLOCK_SIZE = 90;

class Block
{
public:
    int x, y; // ブロックの位置
    int xp, yp; // ブロックの位置
    int shape; // ブロックの形状（0: 正方形, 1: 三角形）
    int rotation; // ブロックの回転（0: 0度, 1: 90度, 2: 180度, 3: 270度）


    //int blockimg[6];




    int CompBlock[1][4][4] = { 0 };	//お手本、影ブロック用

    int PartsBlock[1][4][4] = { 0 };	//次のブロック用


public:
    Block();
    ~Block();
    void Draw();

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

