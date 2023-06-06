#include "Help.h"
#include "DxLib.h"
#define FADE_TIME 300



//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Help::Help()
{
	//title_font = CreateFontToHandle("Algerian", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	menu_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	//background_image = LoadGraph("Images/Scene/Titleimage.png");

	//if ((background_music = LoadSoundMem("Sounds/BGM/Title.wav")) == -1) {
	//	throw "Sounds/BGM/Title.wav";
	//}

	//if ((enter_se = LoadSoundMem("Resource/Sounds/SE/enter.mp3")) == -1) {
	//	throw "Resource/Sounds/SE/enter.mp3";
	//}

	//if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.mp3")) == -1)
	//{
	//	throw "Resource/Sounds/SE/cursor_move.mp3";
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
// �f�X�g���N�^
//-----------------------------------
Help::~Help()
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
// �X�V
//-----------------------------------
AbstractScene* Help::Update()
{
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

	// ����Ԋu����
	const int max_input_margin = 15;

	// �X�e�B�b�N�̊��x
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

		// �X�e�B�b�N��Y���W��擾
		//int stick_y = PAD_INPUT::GetLStick().y;

		//if (std::abs(stick_y) > stick_sensitivity) {

		//	PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);

		//	// �X�e�B�b�N����Ɉړ������ꍇ
		//	if (stick_y > 0) {
		//		// ���j���[�I������O�Ɉړ�
		//		select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		//	}
		//	// �X�e�B�b�N�����Ɉړ������ꍇ
		//	else if (stick_y < 0) {
		//		// ���j���[�I��������Ɉړ�
		//		select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		//	}

		//	input_margin = 0;

		//}

#ifdef TITLE_DEBUG
		if (std::abs(PAD_INPUT::GetLStick().x) > stick_sensitivity) {

			PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);
			is_select_debug = !is_select_debug;
			input_margin = 0;

		}
#endif // TITLE_DEBUG

	}

	//
	//	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	//	{
	//
	//		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
	//		while (CheckSoundMem(enter_se)) {}
	//
	//#ifdef TITLE_DEBUG
	//		if (is_select_debug == true) {
	//			return new DotByDot();
	//		}
	//#endif // TITLE_DEBUG
	//
	//
	//		input_margin = 0;
	//		MENU current_selection = static_cast<MENU>(select_menu);
	//
	//		switch (current_selection)
	//		{
	//		case Title::MENU::PLAY:
	//			return new GameMain(1, element_volume, pouch);
	//			break;
	//
	//		case Title::MENU::HELP:
	//		{
	//			GameMain* help = new GameMain(0, element_volume, pouch);
	//			help->SetHelpMode(true);
	//			return help;
	//			break;
	//		}
	//		case Title::MENU::EXIT:
	//			return new Credit();
	//			break;
	//
	//		default:
	//			printfDx("�������ȋ@�\�ł��B\n");
	//			break;
	//		}
	//
	//	}

	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void Help::Draw()const
{

	int bright = static_cast<int>((static_cast<float>(fade_counter) / FADE_TIME * 255));
	SetDrawBright(bright, bright, bright);

	//DrawGraph(0, 0, background_image, FALSE);
	//DrawStringToHandle(GetDrawCenterX("Science Revenge", title_font), 100, "Science Revenge", 0x66290E, title_font, 0xFFFFFF);

	for (int i = 0; i < static_cast<int>(MENU::MENU_SIZE); i++)
	{
		// ������̍ŏ�Y���W
		const int base_y = 400;

		// �������Y���W�Ԋu
		const int margin_y = 100;

		// �����F
		int color = 0xFFFFFF;
		// �����O�g�F
		int border_color = 0x000000;

		// �����x
		int transparency = 180;

#ifdef TITLE_DEBUG

		// �����F
		int debug_color = 0xFFFFFF;
		// �����O�g�F
		int debug_border_color = 0x000000;

		// �����x
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

		// �J�[�\���������Ă���ꍇ�A�����F�ƕ����O�g�F�𔽓]������
		if (select_menu == i) {
			color = ~color;
			border_color = ~border_color;
			transparency = 255;
		}

#endif // TITLE_DEBUG

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
		DrawStringToHandle(GetDrawCenterX(menu_items[i], menu_font), i * margin_y + base_y, menu_items[i], color, menu_font, border_color);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


}