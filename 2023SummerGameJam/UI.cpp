#include "GameMain.h"
#include "DxLib.h"
#define FADE_TIME 300
#define Limit 60
#define HEIGHT 8
#define WIDTH 12

int Stage[HEIGHT][WIDTH]; //ステージ配列 ブロック配置可能箇所
int backImg;
int blockimg[6];

int blockList[1][4][4]{
	{{0,2,3,0},{2,1,1,3},{4,1,1,5},{0,4,5,0}}
};

int gNewBlock[4][4] = { 0 };	//新しいブロック用
int gNextBlock[4][4] = { 0 };	//次のブロック用

int TimeCount = 0;
int Time = 0;


//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	//title_font = CreateFontToHandle("Algerian", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	backImg = LoadGraph("img/backimg.png");
	LoadDivGraph("img/block.png", 6, 6, 1, 90, 90, blockimg);

	//if ((background_music = LoadSoundMem("Sounds/BGM/Title.wav")) == -1) {
	//	throw "Sounds/BGM/Title.wav";
	//}

	//if ((enter_se = LoadSoundMem("Sounds/SE/enter.mp3")) == -1) {
	//	throw "Sounds/SE/enter.mp3";
	//}

	//if ((cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3")) == -1)
	//{
	//	throw "Sounds/SE/cursor_move.mp3";
	//}


	select_se = 0;
	decision_se = 0;

	input_margin = 0;

#ifdef TITLE_DEBUG
	is_select_debug = false;
#endif // TITLE_DEBUG


	select_menu = static_cast<int>(MENU::PLAY);

	fade_counter = 0;

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
	DeleteFontToHandle(menu_font);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{
//	if (fade_counter < FADE_TIME)
//	{
//		fade_counter++;
//	}
//
//#ifndef TITLE_DEBUG
//	if (fade_counter < FADE_TIME)
//	{
//		return this;
//	}
//#endif // !TITLE_DEBUG
//
//	// 操作間隔時間
//	const int max_input_margin = 15;
//
//	// スティックの感度
//	const int stick_sensitivity = 20000;
//
//	if (input_margin < max_input_margin)
//	{
//		input_margin++;
//	}
//	else {
//
//		// スティックのY座標を取得
//		//int stick_y = PAD_INPUT::GetLStick().y;
//
//		//if (std::abs(stick_y) > stick_sensitivity) {
//
//		//	PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
//
//		//	// スティックが上に移動した場合
//		//	if (stick_y > 0) {
//		//		// メニュー選択肢を一つ前に移動
//		//		select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
//		//	}
//		//	// スティックが下に移動した場合
//		//	else if (stick_y < 0) {
//		//		// メニュー選択肢を一つ次に移動
//		//		select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
//		//	}
//
//		//	input_margin = 0;
//
//		//}
//
//#ifdef TITLE_DEBUG
//		if (std::abs(PAD_INPUT::GetLStick().x) > stick_sensitivity) {
//
//			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
//			is_select_debug = !is_select_debug;
//			input_margin = 0;
//
//		}
//#endif // TITLE_DEBUG
//
//	}
//
//	//
//	//	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
//	//	{
//	//
//	//		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
//	//		while (CheckSoundMem(enter_se)) {}
//	//
//	//#ifdef TITLE_DEBUG
//	//		if (is_select_debug == true) {
//	//			return new DotByDot();
//	//		}
//	//#endif // TITLE_DEBUG
//	//
//	//
//	//		input_margin = 0;
//	//		MENU current_selection = static_cast<MENU>(select_menu);
//	//
//	//		switch (current_selection)
//	//		{
//	//		case Title::MENU::PLAY:
//	//			return new GameMain(1, element_volume, pouch);
//	//			break;
//	//
//	//		case Title::MENU::HELP:
//	//		{
//	//			GameMain* help = new GameMain(0, element_volume, pouch);
//	//			help->SetHelpMode(true);
//	//			return help;
//	//			break;
//	//		}
//	//		case Title::MENU::EXIT:
//	//			return new Credit();
//	//			break;
//	//
//	//		default:
//	//			printfDx("未実装な機能です。\n");
//	//			break;
//	//		}
//	//
//	//	}

int r = 0;

//ブロック作成
//新しいブロックをセット＆次のブロックを生成
for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
		gNewBlock[i][j] = blockList[r][i][j];
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

	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void GameMain::Draw()const
{

	//int bright = static_cast<int>((static_cast<float>(fade_counter) / FADE_TIME * 255));
	//SetDrawBright(bright, bright, bright);

	DrawGraph(0, 0, backImg, FALSE);/*
	DrawGraph(40, 40, block[0], FALSE);
	DrawGraph(130, 130, block[1], TRUE);*/


	////ステージ配列表示
	//for (int i = 0; i < HEIGHT; i++) {
	//	for (int j = 0; j < WIDTH; j++) {
	//		if (Stage[i][j] != 2) {
	//			DrawGraph((j+7) * 90, (i+0) * 90, blockimg[1], TRUE);
	//		}
	//	}
	//}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//NEWブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				DrawGraph( 90*(j+11),90*(i+2), blockimg[gNewBlock[i][j]], TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//お題ブロックを描画
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (gNewBlock[i][j] != 0) {
				DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2),0.8,0, blockimg[gNewBlock[i][j]], TRUE);
			}
		}
	}


	////ステージの値でブロックを表示　下の方
	//for (int i = 0; i <2; i++) {
	//	for (int j = 0; j < 14; j++) {
	//		if (Stage[i][j] != 1) {
	//			DrawGraph((j + 6) * 90, (i + 9) * 90, blockimg[Stage[i][j]], TRUE);
	//		}
	//	}
	//}

	SetFontSize(40);
	DrawString(150, 20, "お題", 0x000000);
	DrawString(120, 400, "制限時間", 0x000000);
	DrawFormatString(120, 500, 0x000000, "%d",Time);

	//DrawStringToHandle(GetDrawCenterX("Science Revenge", title_font), 100, "Science Revenge", 0x66290E, title_font, 0xFFFFFF);

}