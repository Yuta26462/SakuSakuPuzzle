#include "BlockManager.h"
#include "DxLib.h"


BlockManager::BlockManager(POSITION posittion)
{
    POSITION sample_posittion = { 200,200};

    // 初期のブロックの生成
    for (int i = 0; i < 6; i++) {
        Block block;
        block.x = i * BLOCK_SIZE + sample_posittion.x;
        block.y = 0 + sample_posittion.y;
        block.shape = GetRand(1); // 0または1のランダムな値
        block.rotation = 0;
        sampleBlocks.push_back(block);
    }

    // お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
            Block block;
            block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
            block.y = sampleBlock.y + posittion.y;
            block.shape = sampleBlock.shape;
            block.rotation = sampleBlock.rotation;
            playerBlocks.push_back(block);
        }
    }
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

        bool isMatch = false;
    for (int i = 0; i < sampleBlocks.size(); i++) {
        if (sampleBlocks[i].x != playerBlocks[i].x || sampleBlocks[i].y != playerBlocks[i].y ||
            sampleBlocks[i].shape != playerBlocks[i].shape || sampleBlocks[i].rotation != playerBlocks[i].rotation) {
            isMatch = false;
            break;
        }
    }
    if (isMatch) {
        // スコアを加算
        // TODO: 新しいお手本のブロックを生成
    }
    // スコアが増えるたびにブロックの分割数を増やす

}

void BlockManager::GenerationExsampleBlock()
{
    sampleBlocks.clear();
    playerBlocks.clear();

    POSITION posittion = { 1000,760 };
    POSITION sample_posittion = { 200,200 };

    // 初期のブロックの生成
    for (int i = 0; i < 6; i++) {
        Block block;
        block.x = i * BLOCK_SIZE + sample_posittion.x;
        block.y = 0 + sample_posittion.y;
        block.shape = GetRand(1); // 0または1のランダムな値
        block.rotation = 0;
        sampleBlocks.push_back(block);
    }

    // お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
            Block block;
            block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
            block.y = sampleBlock.y + posittion.y;
            block.shape = sampleBlock.shape;
            block.rotation = sampleBlock.rotation;
            playerBlocks.push_back(block);
        }
    }

}

void BlockManager::GenerationPlayerBlock()
{
    playerBlocks.clear();
	POSITION posittion = { 1000,760 };
	POSITION sample_posittion = { 200,200 };
	// お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
			Block block;
			block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
			block.y = sampleBlock.y + posittion.y;
			block.shape = sampleBlock.shape;
			block.rotation = sampleBlock.rotation;
			playerBlocks.push_back(block);
		}
	}
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

