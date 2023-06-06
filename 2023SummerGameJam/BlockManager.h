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

	// ����{�ƃv���C���[�̃u���b�N���i�[����x�N�^�[
	std::vector<Block> sampleBlocks;
	std::vector<Block> playerBlocks;

	// �u���b�N�̕������i�����l��3�j
	int splitNum = 3;

public:
	BlockManager(POSITION posittion = {1000,760});
	~BlockManager();
	void Draw();
	void Update();
};

