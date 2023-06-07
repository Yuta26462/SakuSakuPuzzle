#include "BlockManager.h"
#include "DxLib.h"

BlockManager::BlockManager(POSITION posittion)
{

    LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);

    POSITION sample_posittion = { 200,200};

   

    // 初期のブロックの生成
    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 4; j++) {

            Block block;
            block.CompBlock[r][i][j] = CompblockList[r][i][j];

            block.x = 90 * (j + 11);
            block.y = 90 * (i + 2);

            if (block.CompBlock[r][i][j] <= 2) {
                block.shape = 1;
            }
            else {
                block.shape = 0;
            }
            block.rotation = 0;

            sampleBlocks.push_back(block);
        }
    }


    for (int i = 0; i < 4; i++)
    {
        Block block;
        for (int j = 0; j < 4; j++)
        {
            block.PartsBlock[0][i][j] = PBlockList[r][i][j];

            block.xp =(j+3) * BLOCK_SIZE + (i*270);
            block.yp = (j+5) * BLOCK_SIZE;

            if (block.PartsBlock[0][i][j] <= 2) {
                block.shape = 1;
            }
            else {
                block.shape = 0;
            }
            block.rotation = 0;
        }

        playerBlocks.push_back(block);
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
}


BlockManager::~BlockManager() = default;

void BlockManager::Draw()
{
    // ブロックの描画
    for (Block& block : sampleBlocks) {
        block.Draw();
    }
    for (Block& block : playerBlocks) {
        block.Draw();
    }
}

void BlockManager::Update()
{
    // 形状のマッチングとスコアの更新
        // TODO: お手本のブロックとプレイヤーのブロックが一致しているか確認し、スコアを更新

    //    bool isMatch = false;
    //for (int i = 0; i < sampleBlocks.size(); i++) {
    //    if (sampleBlocks[i].x != playerBlocks[i].x || sampleBlocks[i].y != playerBlocks[i].y ||
    //        sampleBlocks[i].shape != playerBlocks[i].shape || sampleBlocks[i].rotation != playerBlocks[i].rotation) {
    //        isMatch = false;
    //        break;
    //    }
    //}
    //if (isMatch) {
    //    // スコアを加算
    //    // TODO: 新しいお手本のブロックを生成
    //}
    // スコアが増えるたびにブロックの分割数を増やす

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

