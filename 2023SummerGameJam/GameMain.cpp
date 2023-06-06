#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

#define FADE_TIME 300



//-----------------------------------
// コンストラクタ
//-----------------------------------
GameMain::GameMain()
{
	title_font = CreateFontToHandle("メイリオ", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	//menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/game_main.png");

	block_manager = new BlockManager();
	bomb = new Bomb();

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
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* GameMain::Update()
{

	block_manager->Update();

	if(PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		block_manager->GenerationExsampleBlock();
	}

	bomb->Update();
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

	block_manager->Draw();
	bomb->Draw();
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