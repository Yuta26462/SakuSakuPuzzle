#include "Block.h"
#include "DxLib.h"
#include "BlockManager.h"

#include "PadInput.h"

int MoveFlg = 0;
int hit = 0;
int hitblock = 0;
int cx = 0;
int cy = 0;

//iが一つの塊
int o = 0;



Block::Block()
{
	is_hold = false;
}

Block::~Block() {

}

void Block::Update() {
}



void Block::Draw(int blockimg[6])
{
	if (shape > 0) {
		DrawGraph(xp, yp, blockimg[shape], TRUE);
	}

}



void Block::flg(int Moveflg) {
	MoveFlg = Moveflg;
}


void Block::Hit(int Hitblock) {
	hit = Hitblock;
}

void Block::Drawp(int blockimg[6]) {

	DrawFormatString(0, 0, 0x000000, "MoveFlg%d", MoveFlg);

	DrawFormatString(0, 100, 0x000000, "x%d", cx);
	DrawFormatString(0, 150, 0x000000, "y%d", cy);
	//動くｘとｙを出す
	//初期値がカーソル

	////パーツブロックを表示　下の方

	//for (int i = 0; i < 2; i++)
	//{
	//	for (int j = 0; j < 2; j++)
	//	{
	//		if (PartsBlock[0][i][j] != 0)
	//		{

	//			DrawGraph(xp, yp, blockimg[PartsBlock[0][i][j]], TRUE);
	//			if (MoveFlg == 1 && hit == 1 || hitblock == 1) {

	//				hitblock = 1;
	//				xp = cx;
	//				yp = cy;
	//				//DrawGraph(cx + i * BLOCK_SIZE, cy, blockimg[PartsBlock[0][i][j]], TRUE);
	//			}
	//			//else {
	//			//	//1つで表示してるからelseで全部消える
	//			//	DrawGraph(xp, yp, blockimg[PartsBlock[0][i][j]], TRUE);
	//			//}


	//			if (hitblock == 1 && MoveFlg == 0) {
	//				hitblock = 0;
	//			}
	//		}
	//	}
	//}

	//for (int i = 2; i < 4; i++)
	//{
	//	for (int j = 0; j < 2; j++)
	//	{
	//		if (PartsBlock[0][i][j] != 0)
	//		{

	//			DrawGraph(xp, yp, blockimg[PartsBlock[0][i][j]], TRUE);
	//			if (MoveFlg == 1 && hit == 2 || hitblock == 2) {
	//				hitblock = 2;
	//				xp = cx;
	//				yp = cy;
	//			}/*
	//			else
	//			{
	//				DrawGraph(xp, yp, blockimg[PartsBlock[0][i][j]], TRUE);
	//			}*/

	//			if (hitblock == 2 && MoveFlg == 0) {
	//				hitblock = 0;
	//			}
	//		}
	//	}
	//}

}


void Block::rotate()
{
	//作業用
	int temp[1][4][4] = { 0 };


	////ブロックを回転して一時保存
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		temp[0][j][3 - i] = PartsBlock[0][i][j];
	//	}
	//}

	////回転後のデータを転記
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		PartsBlock[0][i][j] = temp[0][i][j];
	//	}
	//}
}