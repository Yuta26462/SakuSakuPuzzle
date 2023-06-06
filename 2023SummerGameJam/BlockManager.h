#pragma once
#include <vector>
#include "Block.h"

struct POSITION
{
	int x;
	int y;
};

class BlockManager
{
private:

	// お手本とプレイヤーのブロックを格納するベクター
	std::vector<Block> sampleBlocks;
	std::vector<Block> playerBlocks;

	// ブロックの分割数（初期値は3）
	int splitNum = 3;

public:
	BlockManager(POSITION posittion = {1000,760});
	~BlockManager();
	void Draw();
	void Update();
};

