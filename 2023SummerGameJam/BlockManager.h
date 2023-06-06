#pragma once
#include <vector>
#include "Block.h"

class BlockManager
{
private:

	// お手本とプレイヤーのブロックを格納するベクター
	std::vector<Block> sampleBlocks;
	std::vector<Block> playerBlocks;

	// ブロックの分割数（初期値は3）
	int splitNum = 3;

public:
	BlockManager();
	~BlockManager();
	void Draw();
	void Update();
};

