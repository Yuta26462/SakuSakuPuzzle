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

	// ����{�̃u���b�N���i�[����x�N�^�[
	std::vector<Block> sampleBlocks;
	// �v���C���[�̃u���b�N���i�[����x�N�^�[
	std::vector<Block> playerBlocks;
	// �L�����o�X�̃u���b�N���i�[����x�N�^�[
	std::vector<Block> canvas;

	// �u���b�N�̕������i�����l��3�j
	int splitNum = 3;

public:
	BlockManager(POSITION posittion = {1000,760});
	~BlockManager();
	void Draw();
	void Update();
	/// <summary>
	/// ����{�u���b�N�𐶐�
	/// </summary>
	void GenerationExsampleBlock();
	/// <summary>
	/// �v���C���[�u���b�N�𐶐�
	/// </summary>
	void GenerationPlayerBlock();
	/// <summary>
	/// �v���C���[�̕�����Setter
	/// </summary>
	/// <param name = "num">0�`10�܂ł̒l</param>
	void SetSplitNum(int num) {
		if(num < 0 || num > 10) return;
		splitNum = num; 
	};
	
	void Split();
	void Merge();
	void Rotate();
	void Move();
	void Reset();
};

