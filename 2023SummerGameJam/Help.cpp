#include "Help.h"
#include "DxLib.h"
#include "Math.h"
#define FADE_TIME 300
#include "SceneManager.h"
#include "PadInput.h"
#include "GameMain.h"
#include "Title.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
Help::Help()
{
	menu_font = LoadFontDataToHandle("Resource/Fonts/funwari-round_s120.dft");
	normal_font = LoadFontDataToHandle("Resource/Fonts/funwari-round.dft");

	background_image = LoadGraph("Resource/Images/Scene/Title.png");

	gamepad_image = LoadGraph("Resource/Images/gamepad.png");
	star_image = LoadGraph("Resource/Images/2-4a/Star.png");
	bomb_image = LoadGraph("Resource/Images/2-4a/bomb_normal.png");

	background_music = LoadSoundMem("Resource/Sounds/BGM/Result.mp3");
	enter_se = LoadSoundMem("Resource/Sounds/SE/enter.mp3");
	cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.mp3");
	decision_se = 0;

	input_margin = 0;

	fade_counter = 0;

	page = 1;
	star_x = 1600;
	star_y = 450;
	angle_x = 1;
	angle_y = 1;
	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// デストラクタ
//-----------------------------------
Help::~Help()
{
	StopSoundMem(background_music);
	DeleteGraph(background_image);
	DeleteGraph(gamepad_image);
	DeleteSoundMem(enter_se);
	DeleteSoundMem(cursor_move_se);
	DeleteFontToHandle(menu_font);

	SetDrawBright(255, 255, 255);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Help::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)){
		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
		return new GameMain();
	}

	if(PAD_INPUT::OnButton(XINPUT_BUTTON_B)) {
		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
		return new Title();

	}

	if ((PAD_INPUT::GetLStick().x > 20000 || PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT))&& page == 1)
	{
		page = 2;
		PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
	}

	if ((PAD_INPUT::GetLStick().x < -20000 || PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT)) && page == 2)
	{
		page = 1;
		star_x = 1600;
		star_y = 450;
		PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
	}

	if (page == 1 && PAD_INPUT::OnPressed(XINPUT_BUTTON_X) && PAD_INPUT::OnPressed(XINPUT_BUTTON_Y))
	{
		for (int i = 0; i < 100; i++) {
			star_x += angle_x;
			star_y += angle_y;
			if (star_x > 1630)
			{
				angle_x = -GetRand(3) + 1;
			}
			if (star_x < 0)
			{
				angle_x = GetRand(3) + 1;
			}

			if (star_y > 810)
			{
				angle_y = -GetRand(3) + 1;
			}
			if (star_y < 0)
			{
				angle_y = GetRand(3) + 1;
			}
		}
	}

	return this;
}

//-----------------------------------
// 描画
//-----------------------------------
void Help::Draw()const
{
	SetFontSize(50);
	DrawGraph(0, 0, background_image, TRUE);
	DrawStringToHandle(0, 1000, "Bでタイトルへ", 0xff0000, normal_font);
	DrawStringToHandle(1300, 1000, "Aでゲームかいし", 0x00ff00, normal_font);

	switch (page)
	{
	case 1:
		DrawStringToHandle(GetDrawCenterX("ルールせつめい", menu_font), 75, "ルールせつめい", 0x66290E, menu_font);
		DrawStringToHandle(GetDrawCenterX("ひだりうえの　おだいと　おなじかたちを　つくろう", normal_font), 225, "ひだりうえの　おだいと　おなじかたちを　つくろう", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("なんこ　できたか　ともだちと　しょうぶ！", normal_font), 325, "なんこ　できたか　ともだちと　しょうぶ！", 0x000000, normal_font);

		DrawStringToHandle(GetDrawCenterX("せいげんじかん", menu_font), 500, "せいげんじかん", 0x66290E, menu_font);
		DrawStringToHandle(GetDrawCenterX("せいげんじかんが　なくなったら　おしまい", normal_font), 675, "せいげんじかんが　なくなったら　おしまい", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("くりあ　するほど　じかんが　のびるよ！", normal_font), 775, "くりあ　するほど　じかんが　のびるよ！", 0x000000, normal_font);

		DrawGraph(star_x, star_y, star_image, TRUE);
		DrawGraph(25, 350, star_image, TRUE);

		DrawStringToHandle(GetDrawCenterX("1/2", normal_font), 1000, "1/2", 0x000000, normal_font);
		DrawTriangle(1100, 1015, 1125, 1040, 1100, 1065, 0x000000, TRUE);
		DrawTriangle(825, 1015, 800, 1040, 825, 1065, 0x777777, TRUE);
		break;

	case 2:
		DrawGraph(0, -50, gamepad_image, TRUE);
		DrawStringToHandle(GetDrawCenterX("そうさせつめい", menu_font), 25, "そうさせつめい", 0x66290E, menu_font);
		DrawStringToHandle(552, 182, "Aボタン", 0x000000, normal_font);
		DrawStringToHandle(550, 180, "Aボタン", 0x00ff00, normal_font);
		DrawStringToHandle(850, 180, ":つかむ、もってるはこをおく", 0x000000, normal_font);

		DrawStringToHandle(552, 272, "Yボタン", 0x000000, normal_font);
		DrawStringToHandle(550, 270, "Yボタン", 0xffff00, normal_font);
		DrawStringToHandle(850, 270, ":はこをまわす", 0x000000, normal_font);
		DrawString(1350, 290,"（未実装）" ,0x000000);

		DrawStringToHandle(322, 362, "STARTボタン", 0x000000, normal_font);
		DrawStringToHandle(320, 360, "STARTボタン", 0x777777, normal_font);
		DrawStringToHandle(850, 360, ":リセット", 0x000000, normal_font);
		DrawString(1200, 380, "（未実装）", 0x000000);

		DrawGraph(1700, 500, bomb_image, TRUE);
		DrawStringToHandle(GetDrawCenterX("ばくだんについて", menu_font), 500, "ばくだんについて", 0x66290E, menu_font);

		DrawStringToHandle(GetDrawCenterX("Xボタンで　 ばくだんを　せんたく！", normal_font) + 2, 667, "Xボタン", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("Xボタンで　 ばくだんを　せんたく！", normal_font),665, "Xボタン", 0x0000ff, normal_font);
		DrawStringToHandle(GetDrawCenterX("Xボタンで　ばくだんを　せんたく！", normal_font), 665, " 　　　で　ばくだんを　せんたく！", 0x000000, normal_font);

		DrawStringToHandle(GetDrawCenterX("せんたくちゅう　Aボタンで 　ブロックを　けせる！", normal_font) + 2, 757, "　　　　　　　　Aボタン", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("せんたくちゅう　Aボタンで 　ブロックを　けせる！", normal_font),755, "　　　　　　　　Aボタン", 0x00ff00, normal_font);
		DrawStringToHandle(GetDrawCenterX("せんたくちゅう　Aボタンで　ブロックを　けせる！", normal_font), 755, "せんたくちゅう　 　　　で　ブロックを　けせる！", 0x000000, normal_font);
		DrawString(1650, 825, "（けせない）", 0x000000);
		DrawStringToHandle(GetDrawCenterX("Bボタンで　 せんたくを　キャンセル", normal_font) + 2, 847, "Bボタン", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("Bボタンで　 せんたくを　キャンセル", normal_font), 845, "Bボタン", 0xff0000, normal_font);
		DrawStringToHandle(GetDrawCenterX("Bボタンで　せんたくを　キャンセル", normal_font), 845, " 　　　で　せんたくを　キャンセル", 0x000000, normal_font);


		DrawStringToHandle(GetDrawCenterX("2/2", normal_font), 1000, "2/2", 0x000000, normal_font);
		DrawTriangle(1100, 1015, 1125, 1040, 1100, 1065, 0x777777, TRUE);
		DrawTriangle(825, 1015, 800, 1040, 825, 1065, 0x000000, TRUE);
		break;
	}
}