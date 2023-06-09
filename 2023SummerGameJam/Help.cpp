#include "Help.h"
#include "DxLib.h"
#include "Math.h"
#define FADE_TIME 300
#include "SceneManager.h"
#include "PadInput.h"
#include "GameMain.h"
#include "Title.h"

//-----------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
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
// �X�V
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
// �`��
//-----------------------------------
void Help::Draw()const
{
	SetFontSize(50);
	DrawGraph(0, 0, background_image, TRUE);
	DrawStringToHandle(0, 1000, "B�Ń^�C�g����", 0xff0000, normal_font);
	DrawStringToHandle(1300, 1000, "A�ŃQ�[��������", 0x00ff00, normal_font);

	switch (page)
	{
	case 1:
		DrawStringToHandle(GetDrawCenterX("���[�����߂�", menu_font), 75, "���[�����߂�", 0x66290E, menu_font);
		DrawStringToHandle(GetDrawCenterX("�Ђ��肤���́@�������Ɓ@���Ȃ����������@���낤", normal_font), 225, "�Ђ��肤���́@�������Ɓ@���Ȃ����������@���낤", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("�Ȃ񂱁@�ł������@�Ƃ������Ɓ@���傤�ԁI", normal_font), 325, "�Ȃ񂱁@�ł������@�Ƃ������Ɓ@���傤�ԁI", 0x000000, normal_font);

		DrawStringToHandle(GetDrawCenterX("�������񂶂���", menu_font), 500, "�������񂶂���", 0x66290E, menu_font);
		DrawStringToHandle(GetDrawCenterX("�������񂶂��񂪁@�Ȃ��Ȃ�����@�����܂�", normal_font), 675, "�������񂶂��񂪁@�Ȃ��Ȃ�����@�����܂�", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("���肠�@����قǁ@�����񂪁@�̂т��I", normal_font), 775, "���肠�@����قǁ@�����񂪁@�̂т��I", 0x000000, normal_font);

		DrawGraph(star_x, star_y, star_image, TRUE);
		DrawGraph(25, 350, star_image, TRUE);

		DrawStringToHandle(GetDrawCenterX("1/2", normal_font), 1000, "1/2", 0x000000, normal_font);
		DrawTriangle(1100, 1015, 1125, 1040, 1100, 1065, 0x000000, TRUE);
		DrawTriangle(825, 1015, 800, 1040, 825, 1065, 0x777777, TRUE);
		break;

	case 2:
		DrawGraph(0, -50, gamepad_image, TRUE);
		DrawStringToHandle(GetDrawCenterX("���������߂�", menu_font), 25, "���������߂�", 0x66290E, menu_font);
		DrawStringToHandle(552, 182, "A�{�^��", 0x000000, normal_font);
		DrawStringToHandle(550, 180, "A�{�^��", 0x00ff00, normal_font);
		DrawStringToHandle(850, 180, ":���ށA�����Ă�͂�������", 0x000000, normal_font);

		DrawStringToHandle(552, 272, "Y�{�^��", 0x000000, normal_font);
		DrawStringToHandle(550, 270, "Y�{�^��", 0xffff00, normal_font);
		DrawStringToHandle(850, 270, ":�͂����܂킷", 0x000000, normal_font);
		DrawString(1350, 290,"�i�������j" ,0x000000);

		DrawStringToHandle(322, 362, "START�{�^��", 0x000000, normal_font);
		DrawStringToHandle(320, 360, "START�{�^��", 0x777777, normal_font);
		DrawStringToHandle(850, 360, ":���Z�b�g", 0x000000, normal_font);
		DrawString(1200, 380, "�i�������j", 0x000000);

		DrawGraph(1700, 500, bomb_image, TRUE);
		DrawStringToHandle(GetDrawCenterX("�΂�����ɂ���", menu_font), 500, "�΂�����ɂ���", 0x66290E, menu_font);

		DrawStringToHandle(GetDrawCenterX("X�{�^���Ł@ �΂�������@���񂽂��I", normal_font) + 2, 667, "X�{�^��", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("X�{�^���Ł@ �΂�������@���񂽂��I", normal_font),665, "X�{�^��", 0x0000ff, normal_font);
		DrawStringToHandle(GetDrawCenterX("X�{�^���Ł@�΂�������@���񂽂��I", normal_font), 665, " �@�@�@�Ł@�΂�������@���񂽂��I", 0x000000, normal_font);

		DrawStringToHandle(GetDrawCenterX("���񂽂����イ�@A�{�^���� �@�u���b�N���@������I", normal_font) + 2, 757, "�@�@�@�@�@�@�@�@A�{�^��", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("���񂽂����イ�@A�{�^���� �@�u���b�N���@������I", normal_font),755, "�@�@�@�@�@�@�@�@A�{�^��", 0x00ff00, normal_font);
		DrawStringToHandle(GetDrawCenterX("���񂽂����イ�@A�{�^���Ł@�u���b�N���@������I", normal_font), 755, "���񂽂����イ�@ �@�@�@�Ł@�u���b�N���@������I", 0x000000, normal_font);
		DrawString(1650, 825, "�i�����Ȃ��j", 0x000000);
		DrawStringToHandle(GetDrawCenterX("B�{�^���Ł@ ���񂽂����@�L�����Z��", normal_font) + 2, 847, "B�{�^��", 0x000000, normal_font);
		DrawStringToHandle(GetDrawCenterX("B�{�^���Ł@ ���񂽂����@�L�����Z��", normal_font), 845, "B�{�^��", 0xff0000, normal_font);
		DrawStringToHandle(GetDrawCenterX("B�{�^���Ł@���񂽂����@�L�����Z��", normal_font), 845, " �@�@�@�Ł@���񂽂����@�L�����Z��", 0x000000, normal_font);


		DrawStringToHandle(GetDrawCenterX("2/2", normal_font), 1000, "2/2", 0x000000, normal_font);
		DrawTriangle(1100, 1015, 1125, 1040, 1100, 1065, 0x777777, TRUE);
		DrawTriangle(825, 1015, 800, 1040, 825, 1065, 0x000000, TRUE);
		break;
	}
}