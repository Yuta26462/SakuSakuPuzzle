#include "BlockManager.h"
#include "DxLib.h"
#include "PadInput.h"
#include <iostream>
#include <math.h>

Block fff;

int a;
int rx, ry, bx, by;

BlockManager::BlockManager(Cursor* cursor, Bomb* bomb, int stage)
{
	LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);

	//POSITION sample_posittion = { 200,200};

	this->cursor = cursor;
	this->bomb = bomb;

	// パーチのブロックの生成
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			Block block;

			block.shape = CompblockList[stage][i][j];
			block.x = 90 * (j + 11);
			block.y = 90 * (i + 2);


			/*block.xp = ((j + 6) * BLOCK_SIZE + (270 * i));
			block.yp = 10 * BLOCK_SIZE;*/

			// 応急処置
			block.xp = ((j + 6) * BLOCK_SIZE + (270 * i));
			block.yp = 3 * BLOCK_SIZE;
			block.is_empty = true;
			block.is_hold = false;
			block.rotation = 0;

			sampleBlocks.push_back(block);
		}
	}


	// 応急処置

	all_block_count = 0;
	for (Block& block : sampleBlocks) {
		if (block.shape != 0) {
			all_block_count++;
		}
	}

	//// お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
	//for (Block const& sampleBlock : sampleBlocks) {
	//    for (int i = 0; i < 1; i++) {
	//        Block block;
	//        block.x = BLOCK_SIZE *  11 + (i * BLOCK_SIZE / splitNum) + posittion.x;
	//        block.y = BLOCK_SIZE*2 + posittion.y;
	//        block.shape = sampleBlock.shape;
	//        block.rotation = sampleBlock.rotation;
	//        playerBlocks.push_back(block);
	//    }
	//}

	/*for (int i = 0; i < sampleBlocks.size(); i++) {
		if (sampleBlocks[i].x != playerBlocks[i].x || sampleBlocks[i].y != playerBlocks[i].y ||
			sampleBlocks[i].shape != playerBlocks[i].shape || sampleBlocks[i].rotation != playerBlocks[i].rotation) {


		}
	}*/

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Block block;
			block.x = 90 * (j + 11);
			block.y = 90 * (i + 2);
			block.shape = CompblockList[stage][i][j];
			block.is_empty = false;
			block.is_hold = false;
			re_block.push_back(block);
			//printfDx("x:%d y:%d shape:%d\n", block.x, block.y, block.shape);
		}
	}

	is_hold = false;
	stage_num = stage;

	is_clear = false;
}


BlockManager::~BlockManager() = default;

void BlockManager::Draw()
{

	// ブロックの描画
	for (Block& block : sampleBlocks) {
		block.Draw(blockimg);

		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		////影ブロックを描画
		//for (int i = 0; i < 2; i++) {
		//	for (int j = 0; j < 2; j++) {
		//		if (block.shape != 0) {
		//			DrawGraph(1080 + i * BLOCK_SIZE, 400 + j * BLOCK_SIZE, blockimg[block.shape], TRUE);
		//		}

		//	}
		//}
		//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		////お題ブロックを描画
		//for (int i = 0; i < 2; i++) {
		//	for (int j = 0; j <2; j++) {
		//		if (block.shape != 0) {
		//			DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2), 0.8, 0, blockimg[CompblockList[block.shape][i][j]], TRUE);
		//		}
		//	}
		//}


	}
	//for (Block& block : playerBlocks) {
	//	block.Drawp(blockimg);
	//}


	//for (int i = 0; i < 4; i++) {

	//	//DrawBox(playerBlocks[i].xp+270, playerBlocks[i].yp , playerBlocks[i].xp + BLOCK_SIZE, playerBlocks[i].yp + BLOCK_SIZE, 0x000000, FALSE);



	//	DrawFormatString(400, 30 * i, 0x000000, "plblocksX%d", playerBlocks[i].xp);

	//	//DrawFormatString(600, 30*i, 0x000000, "plblocksY%d",block[i].xp);
	//}


	//DrawFormatString(0, 50, 0x000000, "BtnFlg%d", BtnFlg);

	//if (a == 1) {

	//	DrawFormatString(300, 300, 0x000000, "Hit");
	//}
	//else if (a == 2) {
	//	DrawFormatString(300, 300, 0x000000, "2Hit");
	//}
	//else {

	//	DrawFormatString(300, 300, 0x000000, "No");
	//}

	// デバック表示
	//for (Block& block : sampleBlocks) {
	//	for (Block& re_b : re_block) {
	//		//DrawCircle(re_b.x, re_b.y, 10.0f, 0x00ffff, TRUE);
	//		//if (block.shape == 0 || re_b.shape == 0)continue;
	//		DrawBox(re_b.x, re_b.y, re_b.x + BLOCK_SIZE, re_b.y + BLOCK_SIZE, 0x00ffff, FALSE);
	//		DrawBox(block.xp, block.yp, block.xp + BLOCK_SIZE, block.yp + BLOCK_SIZE, 0xffffff, FALSE);
	//	}
	//}
}

void BlockManager::Update()
{

	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_START)) {
		Reset();
	}

	CheckBlock();



	// 全プレイヤーブロックが消えたらゲームクリア

	// 残りのブロックを演算
	re_all_block_count = 0;
	for (Block& block : sampleBlocks) {
		if (block.shape != 0) {
			re_all_block_count++;
		}
	}


	if (re_all_block_count <= 0) {
		is_clear = true;
	}

	//printfDx("残りブロック:%d\t\t総数:%d\n", re_all_block_count, all_block_count);
	//holdblock(cursor->GetMousePos().x, cursor->GetMousePos().y);



	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && BtnFlg == 0)
	//{
	//	BtnFlg = 1;
	//	fff.flg(1);
	//}
	//else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && BtnFlg == 1)
	//{
	//	BtnFlg = 0;
	//	fff.flg(0);
	//}


	//if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
	//{
	//	fff.rotate();
	//}


	/* if (BtnFlg == 1) {
		 if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			 BtnFlg = 0;
		 }
	 }*/
}

void BlockManager::GenerationExsampleBlock()
{
	/* sampleBlocks.clear();
	 playerBlocks.clear();

	 POSITION posittion = { 1000,760 };
	 POSITION sample_posittion = { 200,200 };
 */



 ////お題ブロックと影ブロック生成
 //for (int i = 0; i < 4; i++)
 //{
 //    Block block;
 //    
 //    for (int j = 0; j < 4; j++) {
 //      

 //        block.CompBlock[r][i][j] = CompblockList[r][i][j];
 //        block.x = 90 * (j + 11);
 //        block.y = 90 * (i + 2);
 //        if (block.CompBlock[r][i][j] <= 2) {
 //            block.shape = 1;
 //        }
 //        else {
 //            block.shape = 0;
 //        }

 //        block.rotation = 0;
 //    }

 //    sampleBlocks.push_back(block);
 //}



 //// 初期のブロックの生成
 //for (int i = 0; i < 6; i++) {
 //    Block block;
 //    block.x = i * BLOCK_SIZE + sample_posittion.x;
 //    block.y = 0 + sample_posittion.y;
 //    block.shape = GetRand(1); // 0または1のランダムな値

 //    block.rotation = 0;
 //    sampleBlocks.push_back(block);
 //}

 // お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
/* for (Block const& sampleBlock : sampleBlocks) {
	 for (int i = 0; i < 1; i++) {
		 Block block;
		 block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
		 block.y = sampleBlock.y + posittion.y;
		 block.shape = sampleBlock.shape;
		 block.rotation = sampleBlock.rotation;
		 playerBlocks.push_back(block);
	 }
 }*/

}

void BlockManager::GenerationPlayerBlock()
{
	//   playerBlocks.clear();
	   //POSITION posittion = { 1000,760 };
	   //POSITION sample_posittion = { 200,200 };
	   //// お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
	//   for (Block const& sampleBlock : sampleBlocks) {
	//       for (int i = 0; i < 1; i++) {
	   //		Block block;
	   //		block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
	   //		block.y = sampleBlock.y + posittion.y;
	   //		block.shape = sampleBlock.shape;
	   //		block.rotation = sampleBlock.rotation;
	   //		playerBlocks.push_back(block);
	   //	}
	   //}
}

void BlockManager::Split()
{
	// ブロックの分割
}

void BlockManager::Merge()
{
	// ブロックの結合
}

void BlockManager::Rotate()
{
	// ブロックの回転
	for (Block const& playerBlock : sampleBlocks) {

		//作業用
		int temp[4][4] = { 0 };

		////ブロックを回転して一時保存
		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		temp[j][3 - i] = fff.PartsBlock[0][i][j];
		//	}
		//}

		////回転後のデータを転記
		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 4; j++) {
		//		fff.PartsBlock[0][i][j] = temp[i][j];
		//	}
		//}

	}
}

void BlockManager::Move()
{
	// ブロックの移動



}

void BlockManager::Reset()
{
	// ブロックのリセット
		// 初期のブロックの生成
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			Block block;

			block.shape = CompblockList[stage_num][i][j];
			block.x = 90 * (j + 11);
			block.y = 90 * (i + 2);


			block.xp = ((j + 6) * BLOCK_SIZE + (270 * i));
			block.yp = 10 * BLOCK_SIZE;

			block.rotation = 0;

			sampleBlocks.push_back(block);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Block block;
			block.x = 90 * (j + 11);
			block.y = 90 * (i + 2);
			block.shape = CompblockList[stage_num][i][j];
			re_block.push_back(block);
			//printfDx("x:%d y:%d shape:%d\n", block.x, block.y, block.shape);
		}
	}

	is_hold = false;

}


void BlockManager::CheckBlock()
{
	int margin = BLOCK_SIZE;
	Cursor::POSITION _cursor = cursor->GetMousePos();
	//printfDx("%d", all_block_count);

	for (Block& block : sampleBlocks) {
		for (Block& re_b : re_block) {


			//block.xp +=  GetRand(3);
			block.yp += GetRand(stage_num);

			if (block.yp > 700) {
				block.yp = 0;
			}


			// カーソルに追従させる
			if (block.is_hold == true && is_hold == true) {
				block.xp = _cursor.x;
				block.yp = _cursor.y;
			};

			// ブロックを掴む
			if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
				/*if (_cursor.x >= block.xp && _cursor.x <= (block.xp + BLOCK_SIZE) &&
					_cursor.y >= block.yp && _cursor.y <= (block.yp + BLOCK_SIZE))*/
				if (std::abs(block.xp - _cursor.x) <= margin && std::abs(block.yp - _cursor.y) <= margin)
				{
					if (bomb->GetState() == BOMB_STATE::SELECT) {
						block.xp = 0;
						block.yp = 0;
						block.shape = 0;
					}
					block.is_hold = true;
					is_hold = true;
				}
			}

			// 0ブロックは無視する
			if (block.shape == 0) { continue; }
			//printfDx("x:%d y:%d shape:%d\t rx:%d ry:%d rshape:%d", block.x, block.y, block.shape, re_block.x, re_block.y, re_block.shape);
			if (std::abs(block.xp - re_b.x) <= margin && std::abs(block.yp - re_b.y) <= margin) {

				if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

					if ((block.shape != re_b.shape) && block.is_hold == false && is_hold == false) {
						continue;
					}

					if (re_b.is_empty == true) {
						//printfDx("埋まっています");
						continue;
					}

					if (is_hold == true && block.is_hold == true) {
						//printfDx("動いている");
						block.xp = re_b.x;
						block.yp = re_b.y;
					}

					block.is_hold = false;
					is_hold = false;
					re_b.is_empty = true;

					//block.shape = re_b.shape;

				}
			}
		}
	}
}
