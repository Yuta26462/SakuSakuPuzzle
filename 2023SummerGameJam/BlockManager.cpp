#include "BlockManager.h"
#include "DxLib.h"


BlockManager::BlockManager(POSITION posittion)
{

    // 初期のブロックの生成
    for (int i = 0; i < 6; i++) {
        Block block;
        block.x = i * BLOCK_SIZE + posittion.x;
        block.y = 0 + posittion.y;
        block.shape = GetRand(1); // 0または1のランダムな値
        block.rotation = 0;
        sampleBlocks.push_back(block);
    }

    // お手本のブロックをsplitNumの値に応じて分割し、プレイヤーのブロックとして格納
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < splitNum; i++) {
            Block block;
            block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
            block.y = sampleBlock.y + posittion.y;
            block.shape = sampleBlock.shape;
            block.rotation = sampleBlock.rotation;
            playerBlocks.push_back(block);
        }
    }
}


BlockManager::~BlockManager()
{
}

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

        bool isMatch = true;
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
