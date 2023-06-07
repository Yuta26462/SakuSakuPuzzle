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


	int CompblockList[8][4][4]{

	{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{0,1,1,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{0,4,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,4,3,0},{0,2,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,1,1,0},{0,1,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,3,5,0},{0,2,4,0},{0,0,0,0}},
	{{0,0,0,0},{1,1,1,0},{1,4,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{2,1,1,3},{0,0,0,0}},
	//ひし形{{0,2,3,0},{2,1,1,3},{4,1,1,5},{0,4,5,0}}
	};

	int PBlockList[5][4][2]{
		//4まで
		{{0,0},{1,1},{1,1},{0,0}},
		{{0,0},{4,1},{2,1},{0,0}},
		{{2,0},{3,0},{4,0},{5,0}},
		{{0,0},{2,5},{5,2},{0,0}},

	};


	// ブロックの分割数（初期値は3）
	int splitNum = 3;

public:

	int blockimg[6];
	int r = 1;

	//std::vector<std::vector<int>> CompBlock;

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

