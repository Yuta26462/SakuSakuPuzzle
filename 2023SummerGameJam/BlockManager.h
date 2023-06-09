#pragma once
#include <vector>
#include "Block.h"
#include "Cursor.h"
#include "Bomb.h"

struct POSITION
{
	int x;
	int y;
};


class BlockManager
{

private:
	Cursor* cursor;
	Block* block;
	Bomb* bomb;
	// お手本のブロックを格納するベクター
	std::vector<Block> sampleBlocks;
	// プレイヤーのブロックを格納するベクター
	//std::vector<Block> playerBlocks;
	// キャンバスのブロックを格納するベクター
	//std::vector<Block> canvas;

	// お手本
	std::vector<Block> re_block;


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



	// ブロックの分割数（初期値は3）
	int splitNum = 3;

	bool is_hold;

	int stage_num;

	bool is_clear;

	int all_block_count;
	int re_all_block_count;

public:

	int blockimg[6];
	int r = 1;
	int BtnFlg=0;


	int PBlockList[5][4][2]{
		//4まで
		{{0,0},{1,1},{1,1},{0,0}},
		{{4,0},{0,1},{2,0},{0,1}},
		{{2,0},{3,0},{4,0},{5,0}},
		{{0,0},{2,5},{5,2},{0,0}},

	};

	//std::vector<std::vector<int>> CompBlock;

	BlockManager(Cursor *cursor, Bomb *bomb,int stage = 0);
	~BlockManager();
	void Draw();
	void Update();



	void Reset();
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

	void CheckBlock();

	void Split();
	void Merge();
	void Rotate();
	void Move();

	bool GetClearFlg() { return is_clear; }
};

