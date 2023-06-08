#include "BlockManager.h"
#include "DxLib.h"
#include "PadInput.h"

Block fff;

int a;

BlockManager::BlockManager(Cursor* cursor, int stage)
{
	stage = 1;
	LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);

	//POSITION sample_posittion = { 200,200};

	this->cursor = cursor;

	// 初期のブロックの生成
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {

			Block block;

			block.shape = CompblockList[stage][i][j];
			block.x = 90 * (j + 11);
			block.y = 90 * (i + 2);


			block.xp = ((j + 6) * BLOCK_SIZE + (270 * i));
			block.yp = 10 * BLOCK_SIZE;

			block.rotation = 0;

			sampleBlocks.push_back(block);
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


}


BlockManager::~BlockManager() = default;

void BlockManager::Draw()
{
	// ブロックの描画
	for (Block& block : sampleBlocks) {
		block.Draw(blockimg);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		//影ブロックを描画
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (block.shape != 0) {
					DrawGraph(1080 + i * BLOCK_SIZE, 400 + j * BLOCK_SIZE, blockimg[block.shape], TRUE);
				}

			}
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//お題ブロックを描画
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j <2; j++) {
				if (block.shape != 0) {
					DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2), 0.8, 0, blockimg[CompblockList[block.shape][i][j]], TRUE);
				}
			}
		}


	}
	//for (Block& block : playerBlocks) {
	//	block.Drawp(blockimg);
	//}


	//for (int i = 0; i < 4; i++) {

	//	//DrawBox(playerBlocks[i].xp+270, playerBlocks[i].yp , playerBlocks[i].xp + BLOCK_SIZE, playerBlocks[i].yp + BLOCK_SIZE, 0x000000, FALSE);



	//	DrawFormatString(400, 30 * i, 0x000000, "plblocksX%d", playerBlocks[i].xp);

	//	//DrawFormatString(600, 30*i, 0x000000, "plblocksY%d",block[i].xp);
	//}


	DrawFormatString(0, 50, 0x000000, "BtnFlg%d", BtnFlg);

	if (a == 1) {

		DrawFormatString(300, 300, 0x000000, "Hit");
	}
	else if (a == 2) {
		DrawFormatString(300, 300, 0x000000, "2Hit");
	}
	else {

		DrawFormatString(300, 300, 0x000000, "No");
	}

}

void BlockManager::Update()
{

	holdblock(cursor->GetMousePos().x, cursor->GetMousePos().y);

	for (Block& block : sampleBlocks) {
		if (block.is_hold == true) {
			block.xp = cursor->GetMousePos().x;
			block.yp = cursor->GetMousePos().y;
		};
	}

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && BtnFlg == 0)
	{
		BtnFlg = 1;
		fff.flg(1);
	}
	else if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && BtnFlg == 1)
	{
		BtnFlg = 0;
		fff.flg(0);
	}


	if (PAD_INPUT::OnButton(XINPUT_BUTTON_Y))
	{
		fff.rotate();
	}


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
}


void BlockManager::holdblock(int bx, int by) {

	for (Block& block : sampleBlocks) {


		//printfDx("x:%d y:%d\n",block.xp,block.yp);
		printfDx("x:%d y:%d\n", cursor->GetMousePos().x, cursor->GetMousePos().y);
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
			if (bx >= block.xp && bx <= (block.xp + BLOCK_SIZE) &&
				by >= block.yp && by <= (block.yp + BLOCK_SIZE))
			{
				block.is_hold = true;

				/*fff.Hit(1);
				a = 1;*/
				printfDx("hit");
			}
			else {
				block.is_hold = false;
			}
			//else {
			//	fff.Hit(0);
			//	a = 0;
			//}
		}
	}
	//	if (bx >= block.xp+270 && bx <= (block.xp + BLOCK_SIZE * 2) &&
	//		by >= 910 && by <= (910 + BLOCK_SIZE))
	//	{

	//		fff.Hit(2);
	//		a = 2;
	//	}
	//}

}