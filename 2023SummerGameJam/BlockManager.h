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

	// お手本のブロックを格納するベクター
	std::vector<Block> sampleBlocks;
	// プレイヤーのブロックを格納するベクター
	std::vector<Block> playerBlocks;
	// キャンバスのブロックを格納するベクター
	std::vector<Block> canvas;

	// ブロックの分割数（初期値は3）
	int splitNum = 3;

public:
	BlockManager(POSITION posittion = {1000,760});
	~BlockManager();
	void Draw();
	void Update();
	/// <summary>
	/// お手本ブロックを生成
	/// </summary>
	void GenerationExsampleBlock();
	/// <summary>
	/// プレイヤーブロックを生成
	/// </summary>
	void GenerationPlayerBlock();
	/// <summary>
	/// プレイヤーの分割数Setter
	/// </summary>
	/// <param name = "num">0～10までの値</param>
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

