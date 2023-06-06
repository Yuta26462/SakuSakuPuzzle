#include "Title.h"
#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"
#include <iostream>


#define FADE_TIME 300



//-----------------------------------
// コンストラクタ
//-----------------------------------
Title::Title()
{
	title_font = CreateFontToHandle("メイリオ", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	//background_image = LoadGraph("Images/Scene/Titleimage.png");

	//if ((background_music = LoadSoundMem("Sounds/BGM/Title.wav")) == -1) {
	//	throw "Sounds/BGM/Title.wav";
	//}

	enter_se = LoadSoundMem("Sounds/SE/enter.mp3");

	cursor_move_se = LoadSoundMem("Sounds/SE/cursor_move.mp3");
	select_se = 0;
	decision_se = 0;

	input_margin = 0;


	select_menu = static_cast<int>(MENU::PLAY);

	fade_counter = 0;

	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// デストラクタ
//-----------------------------------
Title::~Title()
{
	//DeleteGraph(background_image);
	//StopSoundMem(background_music);
	//DeleteSoundMem(background_music);
	DeleteSoundMem(enter_se);
	DeleteSoundMem(cursor_move_se);
	DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Title::Update()
{
	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}

	// 操作間隔時間
	const int max_input_margin = 15;

	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

		// スティックのY座標を取得
		int stick_y = PAD_INPUT::GetLStick().y;

		if (std::abs(stick_y) > stick_sensitivity) {

			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);

			// スティックが上に移動した場合
			if (stick_y > 0) {
				// メニュー選択肢を一つ前に移動
				select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
			}
			// スティックが下に移動した場合
			else if (stick_y < 0) {
				// メニュー選択肢を一つ次に移動
				select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
			}

			input_margin = 0;

		}

	}

	
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
		{
	
			PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
			while (CheckSoundMem(enter_se)) {}
	
	
	
			input_margin = 0;
			MENU current_selection = static_cast<MENU>(select_menu);
	
			switch (current_selection)
			{
			case Title::MENU::PLAY:
				return new GameMain();
				break;


			case Title::MENU::EXIT:
				return nullptr;
				break;
	
			default:
				printfDx("未実装な機能です。\n");
				break;
			}
	
		}

	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Title::Draw()const
{

	int bright = static_cast<int>((static_cast<float>(fade_counter) / FADE_TIME * 255));
	SetDrawBright(bright, bright, bright);

	//DrawGraph(0, 0, background_image, FALSE);
	DrawStringToHandle(GetDrawCenterX("さくさくパズル", title_font), 100, "", 0x66290E, title_font, 0xFFFFFF);

	for (int i = 0; i < static_cast<int>(MENU::MENU_SIZE); i++)
	{
		// 文字列の最小Y座標
		const int base_y = 400;

		// 文字列のY座標間隔
		const int margin_y = 100;

		// 文字色
		int color = 0xFFFFFF;
		// 文字外枠色
		int border_color = 0x000000;

		// 透明度
		int transparency = 180;


		// カーソルが合っている場合、文字色と文字外枠色を反転させる
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
			transparency = 255;
		}

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


}