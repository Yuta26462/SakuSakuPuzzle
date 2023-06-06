#pragma once

// ブロックのサイズ
const int BLOCK_SIZE = 80;

class Block
{
public:
    int x, y; // ブロックの位置
    int shape; // ブロックの形状（0: 正方形, 1: 三角形）
    int rotation; // ブロックの回転（0: 0度, 1: 90度, 2: 180度, 3: 270度）

public:
    void Draw();

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

