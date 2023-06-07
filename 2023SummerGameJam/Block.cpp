#include "Block.h"
#include "DxLib.h"
#include "BlockManager.h"

#include "PadInput.h"

int MoveFlg = 0;
int cx = 0;
int cy = 0;

Block::Block(Cursor* cursor)
{
	this->cursor = cursor;
}

Block::~Block() {

}

void Getc(Cursor::POSITION* cursor)
{
	cx = cursor->x;
	cy = cursor->y;
}

void Block::Update() {

	Cursor::POSITION cursor_pos = cursor->GetMousePos();

	//cursor_pos = cursor->GetMousePos();
	cx = cursor_pos.x;
	cy = cursor_pos.y;
	/*mx = cx;
	my = cy;*/
	BlockManager xx;

	xx.holdblock(cx, cy);

}



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
			if (CompBlock[0][i][j] != 0) {
				DrawGraph(x,y, bm.blockimg[CompBlock[0][i][j]], TRUE);
			}
		}
	}



	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}



void Block::flg(int Moveflg) {
	MoveFlg = Moveflg;
}

void Block::Drawp() {


	DrawFormatString(0, 0, 0x000000, "MoveFlg%d", MoveFlg);

	DrawFormatString(0, 100, 0x000000, "x%d", cx);
	DrawFormatString(0, 150, 0x000000, "y%d", cy);
	BlockManager bm;
	//動くｘとｙを出す
	//初期値がカーソル

	////パーツブロックを表示　下の方

	for (int i = 0; i < 4; i++)
	{
		
		for (int j = 0; j < 2; j++)
		{
			if (PartsBlock[0][i][j] != 0)
			{

				if (MoveFlg == 1) {
				/*	xp = j*BLOCK_SIZE + (i * 270);
					yp = cy;*/

					DrawGraph(cx+j * BLOCK_SIZE,cy, bm.blockimg[PartsBlock[0][i][j]], TRUE);

				
				}
				else {

					DrawGraph(xp, yp, bm.blockimg[PartsBlock[0][i][j]], TRUE);
				}
			}
		}
	}

}