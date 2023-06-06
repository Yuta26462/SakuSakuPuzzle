#include "GameMain.h"
#include "DxLib.h"

#define FADE_TIME 300

#define Limit 60
#define HEIGHT 9
#define WIDTH 10

int Stage[HEIGHT][WIDTH];
int BlockHome[3][HEIGHT][WIDTH]; //ステージ配列 ブロック配置可能箇所
int backImg;
int blockimg[6];

int BlockFlg = TRUE;

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

int PBlockList[6][1][2]{
	{{1,1}},
	{{0.1}},
	{{0,2}},
	{{1,3}},
	{{2,1}},
};

int gNewBlock[4][4] = { 0 };	//新しいブロック用
int gNextBlock[4][4] = { 0 };	//次のブロック用


int TimeCount = 0;
int Time = 0;
int r = 5;


//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	title_font = CreateFontToHandle("メイリオ", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	//menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/game_main.png");

	block_manager = new BlockManager();
	backImg = LoadGraph("img/backimg.png");
	LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);


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
}





//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{


	//ブロック作成
	//新しいブロックをセット＆次のブロックを生成
	//一回だけ作るようにする

	if (BlockFlg == TRUE) {

		BlockFlg = FALSE;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gNewBlock[i][j] = CompblockList[r][i][j];

				gNextBlock[i][j] = PBlockList[r][i][j];
			}
		}	


		for (int c = 0; c < 3; c++) 
		{

			//iは行が下がる
			//iはPBlockList[r][i][j]の見る中身を下げる
			for (int i = 0; i < 1; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					BlockHome[c][i][j] = PBlockList[r][i][j];
				}
			}
		}

		
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (gNewBlock[i][j] != 0) {
					Stage[i][j] = gNewBlock[i][j];
				}
			}
		}


	}



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

		return this;
	
}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{
	DrawGraph(0, 0, background_image, TRUE);

	DrawBox(0, 0, 400, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 0, 400, 1080, 0x000000);
	DrawBox(0, 850, 1920, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 850, 1920, 1080, 0x000000);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//NEWブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <4; j++) {
			if (gNewBlock[i][j] != 0) {
				DrawGraph(90 * (j + 11), 90 * (i + 2), blockimg[gNewBlock[i][j]], TRUE);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//お題ブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2), 0.8, 0, blockimg[gNewBlock[i][j]], TRUE);
			}
		}
	}


	//パーツブロックを表示　下の方
	for (int c = 0; c < 3; c++) {

		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (BlockHome[c][i][j] != 0) {
					DrawGraph((j + 6) * 90+(c*250), (i + 10) * 90, blockimg[BlockHome[c][i][j]], TRUE);
				}
			}
		}

	}
		

		

		//for (int i = 0; i < HEIGHT; i++) {
		//	for (int j = 0; j < WIDTH; j++) {
		//		if (Stage[i][j] != 0) {
		//			DrawGraph((j) * 90, (i) * 90, blockimg[Stage[i][j]], TRUE);
		//		}
		//	}
		//}

	SetFontSize(40);
	DrawString(150, 20, "お題", 0x000000);
	DrawString(120, 400, "制限時間", 0x000000);
	DrawFormatString(120, 500, 0x000000, "%d", Time);


	block_manager->Draw();

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