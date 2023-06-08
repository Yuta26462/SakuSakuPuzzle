#include "END.h"
#include "DxLib.h"
#include "Title.h"
#include "PadInput.h"
#include "GameMain.h"
#include "End.h"

#define FADE_TIME 300
#define OUTFADE_TIME 600

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
END::END()
{
	title_font = LoadFontDataToHandle("Resource/Fonts/funwari-round_s240.dft");

	menu_font = LoadFontDataToHandle("Resource/Fonts/funwari-round_s120.dft");

	background_image = LoadGraph("Resource/Images/Scene/end.png");
	//background_image = LoadGraph("Images/Scene/end.png");

	select_se = 0;
	decision_se = 0;

	input_margin = 0;
	
	for (int i = 0; i < 2; i++)
	{
		fade_counter[i] = 0;
	}

	//fade_counter= 0;

	watting_time = 0;

	time = 0;

	state = STATE::START;
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
END::~END()
{
	/*StopSoundMem(background_music);
	DeleteSoundMem(background_music);*/
	//DeleteSoundMem(enter_se);
	//DeleteSoundMem(cursor_move_se);
	//DeleteGraph(background_image);
	DeleteFontToHandle(title_font);

	DeleteFontToHandle(menu_font);

}

//-----------------------------------
// �X�V
//-----------------------------------
AbstractScene* END::Update()
{
	
	if (fade_counter[0] < FADE_TIME)
	{
		fade_counter[0]++;
		printfDx("�I\n");
	}
	
	/*else if (fade_counter[0] >= FADE_TIME)
	{
		fade_counter[1]--;
		printfDx("ssss\n");
	}*/

	//DelayAnimation(DELAY_ANIMATION_TYPE::FADE_IN, 1.0f);

	/*if (fade_counter[0] < FADE_TIME)
	{
		fade_counter[0]++;
		printfDx("�I\n");
		state = STATE::MIDDLE;
	}
		
	if(state = STATE::MIDDLE && watting_time < 180){
		watting_time++;
		printfDx("�I�I\n");
	}
	else { state = STATE::END; }
	
	
	if (state == STATE::END && fade_counter[1] < 100) {
		fade_counter[1]++;
		printfDx("�I�I�I\n");
	}*/

	
	if (++WaitTime > 400) {
		return new Title;
	}

	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void END::Draw()const
{
	int bright = static_cast<int>((static_cast<float>(fade_counter[0]) / FADE_TIME * 255));
	/*if (fade_counter[0] >= FADE_TIME) {
		bright = static_cast<int>((static_cast<float>(fade_counter[1]) / FADE_TIME * -255));
	}*/
	SetDrawBright(bright, bright, bright);
	
	/*if (fade_counter[0] < FADE_TIME) {

		int bright = static_cast<int>((static_cast<float>(fade_counter[0]) / FADE_TIME * 255));
		SetDrawBright(bright, bright, bright);
	}
	
	if (fade_counter[1] < 100) {

		int bright = static_cast<int>((static_cast<float>(fade_counter[1]) / FADE_TIME * -255));
		SetDrawBright(bright, bright, bright);
	}*/
	DrawGraph(0, 0, background_image, FALSE);

	DrawStringToHandle(GetDrawCenterX("�������Ă����傤", title_font), 80, "�������Ă����傤", 0xE1D000, title_font, 0xFFFFFF);

	DrawStringToHandle(GetDrawCenterX("BGM", menu_font), 300, "BGM", 0xff0000, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("���܂ڂ�������", menu_font), 420, "���܂ڂ�������", 0x0000f0, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("yuhei komatsu", menu_font), 520, "yuhei komatsu", 0x0000f0, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("SE", menu_font), 650, "SE", 0xff0000, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("���������񃉃{", menu_font), 780, "���������񃉃{", 0x0000f0, menu_font, 0xFFFFFF);

}

//bool END::DelayAnimation(DELAY_ANIMATION_TYPE type, float time)
//{
//	//�A�j���[�V�����̒x��
//	if (delay_animation_count < static_cast<int>(time))
//	{
//		int bright;
//		switch (type)
//		{
//		case END::DELAY_ANIMATION_TYPE::FADE_IN:
//			// �t�F�[�h�C��
//			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * 255));
//			SetDrawBlendMode(DX_BLENDMODE_ADD_X4, bright);
//			//DrawBox(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(0, 0, 0), TRUE);
//			break;
//		case END::DELAY_ANIMATION_TYPE::FADE_OUT:
//			// �t�F�[�h�A�E�g
//			bright = static_cast<int>((static_cast<float>(delay_animation_count) / time * -255) + 255);
//			SetDrawBright(bright, bright, bright);
//			break;
//		default:
//			break;
//		}
//
//		delay_animation_count++;
//		return false;
//	}
//	else
//	{
//		delay_animation_count = 0;
//		return true;
//	}
//
//	return false;
//}
