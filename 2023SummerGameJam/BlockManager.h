#pragma once
#include <vector>
#include "Block.h"

class BlockManager
{
private:

	// ����{�ƃv���C���[�̃u���b�N���i�[����x�N�^�[
	std::vector<Block> sampleBlocks;
	std::vector<Block> playerBlocks;

	// �u���b�N�̕������i�����l��3�j
	int splitNum = 3;

public:
	BlockManager();
	~BlockManager();
	void Draw();
	void Update();
};

