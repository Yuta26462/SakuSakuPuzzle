#include "Result.h"
#include "GameMain.h"//scoreが言っている変数を持ってきたいため
#include "SceneManager.h"
#include"Ranking.h"
#include"GameMain.h"
#include"PadInput.h"

#include <math.h>
#include "DxLib.h"
#define FADE_TIME 300

//-----------------------------------
// コンストラクタ
//-----------------------------------
Result::Result()//クラス　リザルト
{
	count = 0;

	//title_font = CreateFontToHandle("Algerian", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/clear.png");
	//↑画像を差し込む
	Result_BGM = LoadSoundMem("Resource/Sounds/BGM/Result.mp3");
	PlaySoundMem(Result_BGM, DX_PLAYTYPE_LOOP, TRUE);

	//↑音楽を差し込む

	//if ((enter_se = LoadSoundMem("Sounds/SE/enter.mp3")) == -1) {
	//	throw "Sounds/SE/enter.mp3";
	//}

	//↑SEを差し込む

	//if ((cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3")) == -1)
	//{
	//	throw "Sounds/SE/cursor_move.mp3";
	//}

#ifdef TITLE_DEBUG
	is_select_debug = false;
#endif // TITLE_DEBUG
}

//-----------------------------------
// デストラクタ
//-----------------------------------
Result::~Result()
{
	DeleteGraph(background_image);
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
AbstractScene* Result::Update()
{
	if (count < 60)
	{
		count++;
		
	}
	//if(count1>180 && ランキング5位よりスコアが上なら){   return new InputName();  
	if (count>=60 && PAD_INPUT::OnButton(XINPUT_BUTTON_A))	//countは連打などによる押しミス防止												//}else{ return new Ranking}
	{
		return new Ranking();//ボタンAが押されたらランキング、または名前入力画面に遷移
	}

	printfDx("%d\n", count);

	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}

#ifndef TITLE_DEBUG
	if (fade_counter < FADE_TIME)
	{
		return this;
	}
#endif // !TITLE_DEBUG

	// 操作間隔時間
	const int max_input_margin = 15;

	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

#ifdef TITLE_DEBUG
		if (std::abs(PAD_INPUT::GetLStick().x) > stick_sensitivity) {

			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
			is_select_debug = !is_select_debug;
			input_margin = 0;

		}
#endif // TITLE_DEBUG

	}
	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Result::Draw()const//処理したものをここに表示　Clear数の表示はここ
{

	/*追加したもの*/
	DrawGraph(0, 0, background_image, TRUE);
	int gScore = 3;//仮変数

	SetFontSize(100);
	DrawFormatString(1450, 565, 0xffffff, "%d", gScore); //スコア数表示（仮）

	
	/*DrawString(1550, 665,"Aボタンで画面を移動",0xffffff);*/
	//DrawStringToHandle(DrawFormatString(1450,565,0xffffff,"%d",gScore, Result_font), 100, "%d",gScore, 0xffffff, Result_font, 0xFFFFFF);

#ifdef TITLE_DEBUG

		// 文字色
		int debug_color = 0xFFFFFF;
		// 文字外枠色
		int debug_border_color = 0x000000;

		// 透明度
		int debug_transparency = 100;

		if (is_select_debug == true) {
			debug_color = ~color;
			debug_border_color = ~border_color;
			debug_transparency = 255;

		}
		else if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
			transparency = 255;
		}


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, debug_transparency);
		DrawStringToHandle(100, 600, "DEBUG", debug_color, menu_font, debug_border_color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#else

		
#endif // TITLE_DEBUG

	}