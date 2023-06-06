#include "Block.h"
#include "DxLib.h"

void Block::Draw()
{
    if (shape == 0) {
        DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, 0x00ffff, TRUE);
    }
    else if (shape == 1) {
        DrawTriangle(x, y, x + BLOCK_SIZE, y, x + BLOCK_SIZE / 2, y + BLOCK_SIZE, 0x00ffff, TRUE);
    }
}
