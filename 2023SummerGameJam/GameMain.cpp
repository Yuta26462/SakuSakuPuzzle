#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"
#include "Cursor.h"
#include "Bomb.h"
#include "Block.h"

#define FADE_TIME 300

#define Limit 60
#define HEIGHT 9
#define WIDTH 10

int Stage[HEIGHT][WIDTH];
int BlockHome[8][HEIGHT][WIDTH]; //ステージ配列 ブロック配置可能箇所
int backImg;
int blockimg[6];


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

int CompBlock[4][4] = { 0 };	//お手本、影ブロック用
int PartsBlock[4][4] = { 0 };	//次のブロック用


int TimeCount = 0;
int Time = 0;
int r = 0;

int BtnFlg = FALSE;


struct Blockp {
	int x, y;	//座標
	int px, py;	//パーツ座標
};

struct Blockp BlockPos[HEIGHT][WIDTH]={0};

//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	title_font = LoadFontDataToHandle("Resource/Fonts/funwari-round_title.dft");

	CreateBlock();
	//CheckBlock();
	//menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/game_main.png");

	cursor = new Cursor();
	block_manager = new BlockManager(cursor,0);
	bomb = new Bomb(cursor);
	
	backImg = LoadGraph("img/backimg.png");
	//LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);
	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// デストラクタ
//-----------------------------------
GameMain::~GameMain()
{
	//DeleteGraph(background_image);
	//StopSoundMem(background_music);
	//DeleteSoundMem(background_music);
	//DeleteSoundMem(enter_se);
	//DeleteSoundMem(cursor_move_se);
	//DeleteFontToHandle(title_font);
	//DeleteFontToHandle(menu_font);
	SetDrawBright(255, 255, 255);
	delete block_manager;
	delete bomb;
	delete cursor;
}



//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{

	cursor->Update();

	Cursor::POSITION cursor_pos = cursor->GetMousePos();
	cursor_pos.x;
	cursor_pos.y;

	/*if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1)
	{
		BtnFlg=TRUE;
	}
	else{
		BlockPos[0][0].px = cursor_pos.x;
		BlockPos[0][0].py = cursor_pos.y;
	}*/

	//制限時間
	TimeCount++;
	if (TimeCount > 60) {
		TimeCount = 0;
		Time++;
	}

	if (Time > Limit) {
		Time = 0;
	}

	block_manager->Update();
	bomb->Update();

	if(PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		//block_manager->GenerationExsampleBlock();

	}

		return this;
	
}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{
	//DrawGraph(0, 0, background_image, TRUE);
	DrawBox(0, 0, 1920, 1080, 0xffffff,TRUE);
	DrawBox(0, 0, 400, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 0, 400, 1080, 0x000000);
	DrawBox(0, 850, 1920, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 850, 1920, 1080, 0x000000);

	


	////パーツブロックを表示　下の方
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (PBlockList[r][i][j] != 0)
			{
				DrawGraph(BlockPos[i][j].px, BlockPos[i][j].py, blockimg[PBlockList[r][i][j]], TRUE);
			}
		}
	}*/


	SetFontSize(40);
	DrawString(150, 20, "お題", 0x000000);
	DrawString(120, 400, "制限時間", 0x000000);
	DrawFormatString(120, 500, 0x000000, "%d", Time);



	block_manager->Draw();
	bomb->Draw();

	// カーソル描画
	cursor->Draw();
	DrawBlock();


}


bool GameMain::DelayAnimation(DELAY_ANIMATION_TYPE type, float time)
{
	//アニメーションの遅延
	if (delay_animation_count < static_cast<int>(time))
	{
		int bright;
		switch (type)
		{
		case GameMain::DELAY_ANIMATION_TYPE::FADE_IN:
			// フェードイン
			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * 255));
			SetDrawBlendMode(DX_BLENDMODE_ADD_X4, bright);
			//DrawBox(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
			break;
		case GameMain::DELAY_ANIMATION_TYPE::FADE_OUT:
			// フェードアウト
			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * -255) + 255);
			SetDrawBright(bright, bright, bright);
			break;
		default:
			break;
		}

		delay_animation_count++;
		return false;
	}
	else
	{
		delay_animation_count = 0;
		return true;
	}

	return false;
}	


void GameMain::CheckBlock() {
	/*int c=0;

	switch (r)
	{
	case 0:
		c = 2;

		BlockHome[0][0][0] =1;
		BlockHome[0][0][1] =1;
		
	}*/

	//for (c; c < 2; c++)
	//{

	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int j = 0; j < 2; j++)
	//		{
	//			BlockHome[c][i][j] = PBlockList[r][i][j];
	//		}
	//	}

	//}
}

void GameMain::CreateBlock() {



		//お題ブロックと影ブロック生成
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				CompBlock[i][j] = CompblockList[r][i][j];
				BlockPos[i][j].x = 90 * (j + 11);
				BlockPos[i][j].y = 90 * (i + 2);
			}
		}



		//	for (int i = 0; i < 4; i++)
		//	{
		//		for (int j = 0; j < 2; j++)
		//		{
		//			BlockHome[c][i][j] = PBlockList[r][i][j];
		//		}
		//	}

		//}


		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		if (CompBlock[i][j] != 0) {
		//			Stage[i][j] = CompBlock[i][j];
		//		}
		//	}
		//}


	
}

void GameMain::DrawBlock() const {


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//影ブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (CompBlock[i][j] != 0) {
				DrawGraph(BlockPos[i][j].x, BlockPos[i][j].y, blockimg[CompBlock[i][j]], TRUE);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//お題ブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (CompBlock[i][j] != 0) {
				DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2), 0.8, 0, blockimg[CompBlock[i][j]], TRUE);
			}
		}
	}


	////パーツブロックを表示　下の方

	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (PBlockList[r][i][j] != 0)
			{
				DrawGraph(BlockPos[i][j].px, BlockPos[i][j].py, blockimg[PBlockList[r][i][j]], TRUE);
			}
		}
	}*/



}