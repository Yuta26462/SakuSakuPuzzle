#include "BlockManager.h"
#include "DxLib.h"
#include "PadInput.h"

Block fff;

int a;

BlockManager::BlockManager()
{

    LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);

    //POSITION sample_posittion = { 200,200};

    //cursor = new Cursor();

    // 初期のブロックの生成
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            Block block;
            block.CompBlock[0][i][j] = CompblockList[r][i][j];

            block.x = 90 * (j + 11);
            block.y = 90 * (i + 2);

            if (block.CompBlock[0][i][j] <= 2) {
                block.shape = 1;
            }
            else {
                block.shape = 0;
            }
            block.rotation = 0;

            sampleBlocks.push_back(block);
        }
    }


    //パーツ作成
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Block block;
            block.PartsBlock[0][i][j] = PBlockList[r][i][j];

            block.xp =(j+6) * BLOCK_SIZE;
            block.yp = 10 * BLOCK_SIZE;

            if (block.PartsBlock[0][i][j] <= 2) {
                block.shape = 1;
            }
            else {
                block.shape = 0;
            }
            block.rotation = 0;
            playerBlocks.push_back(block);
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

    for (int i = 0; i <2; i++) {
     
            DrawBox(playerBlocks[i].xp, playerBlocks[i].yp, playerBlocks[i].xp + BLOCK_SIZE, playerBlocks[i].yp + BLOCK_SIZE,0x000000,TRUE);

            DrawFormatString(400, 30*i, 0x000000, "plblocksX%d", playerBlocks[i].xp);
            //DrawFormatString(600, 30*i, 0x000000, "plblocksY%d", playerBlocks[i].yp);
    }


    DrawFormatString(0, 50, 0x000000, "BtnFlg%d", BtnFlg);

    if (a == 1) {

        DrawFormatString(300, 300, 0x000000, "当たってるぞい");
    }
    else {

        DrawFormatString(300, 300, 0x000000, "当たってねえ");
    }

    // ブロックの描画
    for (Block& block : sampleBlocks) {
        block.Draw();
    }
    for (Block& block : playerBlocks) {
        block.Drawp();
    }
}

void BlockManager::Update()
{
    
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) && BtnFlg == 0)
    {
        BtnFlg = 1;
        fff.flg(1);
    }else if(PAD_INPUT::OnButton(XINPUT_BUTTON_A)&&BtnFlg == 1) 
    {
            BtnFlg = 0;
            fff.flg(0);
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
    for (Block const& playerBlock : playerBlocks) {
        //playerBlock.rotation(
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


void BlockManager::holdblock(int& bx, int& by) {

    for (int i = 0; i < 2; i++) {
        if (bx >= playerBlocks[i].xp-12 && bx <= (playerBlocks[i].xp + BLOCK_SIZE) &&
            by >= playerBlocks[i].yp && by <= (playerBlocks[i].yp + BLOCK_SIZE))
        {
            a = 1;
        }
        else
        {
            a = 0;


        }
    }
    
}