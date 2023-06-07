#include "Block.h"
#include "DxLib.h"
#include "BlockManager.h"

Block::Block()
{
}

Block::~Block()= default;

void Block::Draw()
{
  /*  if (shape == 0) {
        DrawBox(x, y, x + BLOCK_SIZE, y + BLOCK_SIZE, 0x00ffff, TRUE);
    }
    else if (shape == 1) {
        DrawTriangle(x, y, x + BLOCK_SIZE, y, x + BLOCK_SIZE / 2, y + BLOCK_SIZE, 0x00ffff, TRUE);
    }*/
	BlockManager bm;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//影ブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (CompBlock[bm.r][i][j] != 0) {
				DrawGraph(x,y, bm.blockimg[CompBlock[bm.r][i][j]], TRUE);
			}
		}
	}

	////パーツブロックを表示　下の方

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (PartsBlock[0][i][j] != 0)
			{
				DrawGraph(xp,yp, bm.blockimg[PartsBlock[0][i][j]], TRUE);
				//被ってるブロックが
			}
		}
	}



	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}
