#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

#define FADE_TIME 300



//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	title_font = CreateFontToHandle("���C���I", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	//menu_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/game_main.png");

	block_manager = new BlockManager();


	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// �f�X�g���N�^
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
// �X�V
//-----------------------------------
AbstractScene* GameMain::Update()
{

	block_manager->Update();

	if(PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		block_manager->GenerationExsampleBlock();
	}

	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void GameMain::Draw()const
{
	DrawGraph(0, 0, background_image, TRUE);

	DrawBox(0, 0, 400, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 0, 400, 1080, 0x000000);
	DrawBox(0, 850, 1920, 1080, 0x94fdff, TRUE);
	DrawLineBox(0, 850, 1920, 1080, 0x000000);

	block_manager->Draw();
}

bool GameMain::DelayAnimation(DELAY_ANIMATION_TYPE type, float time)
{
	//�A�j���[�V�����̒x��
	if (delay_animation_count < static_cast<int>(time))
	{
		int bright;
		switch (type)
		{
		case GameMain::DELAY_ANIMATION_TYPE::FADE_IN:
			// �t�F�[�h�C��
			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * 255));
			SetDrawBlendMode(DX_BLENDMODE_ADD_X4, bright);
			//DrawBox(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
			break;
		case GameMain::DELAY_ANIMATION_TYPE::FADE_OUT:
			// �t�F�[�h�A�E�g
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