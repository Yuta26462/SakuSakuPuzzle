#include "Ranking.h"
#include "DxLib.h"
#define FADE_TIME 300
#define RANKING_DATE 5
#include "GameMain.h"
#include "PadInput.h"
#include "Title.h"

Ranking::RankingData  gRanking[RANKING_DATE];

//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
Ranking::Ranking()
{

	menu_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/title.png");

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
	 //�\����

	//struct RankingData {
		//int		no;
		//char	name[11];
		//long	score;
	//};

	//constexpr auto RANKING_DATA = 5;	//�����L���O�f�[�^�̐�;

	//RankingData gRanking[RANKING_DATA]{};

	//struct RankingData		gRanking[RANKING_DATA]{};

	//char MoziSmall[] = "abcdefghijklmnopqrstuvwxyz";
	//char MoziBig[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//char MoziNumber[] = "0123456789";

	//char MoziFrame[11]{};
	///char MoziWork[2]{};

	select_se = 0;
	decision_se = 0;

	input_margin = 0;

	color = 0x000000;

	input_i = 0;

	buf[10];

	display = 10;

	selecterX = 0;
	selecterY = 0;

	input_char = '0';

	i_space = 0;

    Uplow = 0;


	KeyBoard_X = KEYBORA_X;
	for (int i = 0; i < RANKING_DATA; i++)
	{
		g_Ranking[i].no = i + 1;
		g_Ranking[i].score = 0;
	}
#ifdef TITLE_DEBUG
	is_select_debug = false;
#endif // TITLE_DEBUG


	select_menu = static_cast<int>(MENU::a);

	fade_counter = 0;

	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
Ranking::~Ranking()
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
AbstractScene* Ranking::Update()
{
	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}

#ifndef TITLE_DEBUG
	if (fade_counter < FADE_TIME)
	{

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

		// �X�e�B�b�N��Y���W���擾
		//int stick_y = PAD_INPUT::GetLStick().y;

		//if (std::abs(stick_y) > stick_sensitivity) {

		//	PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);

		//	// �X�e�B�b�N����Ɉړ������ꍇ
		//	if (stick_y > 0) {
		//		// ���j���[�I��������O�Ɉړ�
		//		select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		//	}
		//	// �X�e�B�b�N�����Ɉړ������ꍇ
		//	else if (stick_y < 0) {
		//		// ���j���[�I����������Ɉړ�
		//		select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		//	}

		//	input_margin = 0;

		//}

	}

	}
	
	for (int i = 0; i < RANKING_DATA; i++) {
		color = 0xFFFFFF;
		if (i == 0) { color = 0xfffd3d; }
		else if (i == 1) { color = 0xffbc3d; }
		else if (i == 2) { color = 0xc9c9c9; }
		else { color = 0xFFFFFF; }	

		DrawFormatStringToHandle(60, 160 + i * 50, color, menu_font, "%2d", g_Ranking[i].no);
		DrawFormatStringToHandle(120, 160 + i * 50, color, menu_font, "%9s", g_Ranking[i].name);
		DrawFormatStringToHandle(455, 160 + i * 50, color, menu_font, "%5d", g_Ranking[i].score);
	}
	static char default_char[10] = "_________";			//�����\��
	static char buf[10] = "_________";					//���͒l
	static int input_i = 0;								//���͒l(1����)
	static int errorflg = 0;							//�G���[���o�p�t���O
	static char KeyMap_Qwerty[3][12] = { "QWERTYUIOP","ASDFGHJKL","ZXCVBNM" };

	for (int i = 0; input_i > i; i++) {
		DrawFormatStringToHandle(195 + i * 25, 205, 0xFFFFFF, menu_font, "%c", buf[i]);
	}

	for (int display = 10; input_i < display; display--) {
		DrawFormatStringToHandle(170 + display * 25, 205, 0xFFFFFF, menu_font, "%c", buf[display - 1]);
	}
	static int selecterX = 0;
	static int selecterY = 0;

	static int KeyBoard_X = KEYBORA_X;
	static int KeyBoard_XMrgin = KEYBORA_XMARGIN;
	static int KeyMap = 0;	//�����F�A���t�@�x�b�g��
	static int Uplow = 0;	//�����F������
	
	char input_char = '0';
	if (KeyMap == 0) {
		for (int j = 0; j < 5; j++) {
			for (int i = 1; i < 14; i++) {
				if (input_char < '{' || input_char < '[') {

					if (selecterX + 1 == i && selecterY == j) { DrawFormatString(i * KeyBoard_XMrgin + KeyBoard_X, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", input_char++); }
					else { DrawFormatString(i * KeyBoard_XMrgin + KeyBoard_X, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", input_char++); }
				}
				if (input_char == ':') { input_char = 'a'; j = 1; i = 0; }
				if (input_char == '{') { input_char = 'A'; j = 3; i = 0; }
			}
		}
	}
	 if (KeyMap == 1) {
		DrawCircle(214, 397, 10, 0x000000, 1);
		DrawString(210, 390, "Y", 0xffff00);
		DrawString(234, 390, "�啶���^�������؂�ւ�", 0xFF4500);
		int i_space = 0;
		for (int j = 0; j < 4; j++) {
			for (int i = 1; i < 14; i++) {
				if (input_char < '{' || input_char < '[') {
					if (j == 0) {
						if (selecterX + 1 == i && selecterY == j)DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", input_char++);
						else { DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", input_char++); }
					}
					if (j > 0) {
						input_char = KeyMap_Qwerty[0][0];

						if (selecterX + 1 == i && selecterY == j)DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", KeyMap_Qwerty[j - 1][i - 1] + (Uplow == 1 ? 0 : (char)32));
						else {DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", KeyMap_Qwerty[j - 1][i - 1] + (Uplow == 1 ? 0 : (char)32));
							//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
							//DrawBoxAA((i * KEYBORA_XMARGIN + KeyBoard_X + i_space) - 5,(KEYBORA_Y + KEYBORA_YMARGIN * j)-5, (i * KEYBORA_XMARGIN + KeyBoard_X + i_space) + 20, (KEYBORA_Y + KEYBORA_YMARGIN * j) + 20, color, TRUE);
							//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
						if (j == 1 && i == 10) { i_space = 15; break; }
						if (j == 2 && i == 9) { i_space = 30; break; }
						if (j == 3 && i == 7)break;
					}
				}
				if (input_char == ':') {
					j = 1; i = 0;
				}
			}
		}
	}

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
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		return new Title();
	}

	return this;
}

int Ranking::ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)
	//�t�@�C���I�[�v��
	if ((fp = fopen("Resource/data/rankingdata.txt", "r")) == NULL) {
		//�G���[����

		printf("Ranking Data Error\n");
		return -1;
	}
	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANKING_DATE; i++) {
		int dammy = fscanf(fp, "%2d %10s %10d", &gRanking[i].no, gRanking[i].name, &gRanking[i].score);
	}
	return 0;
}

//-----------------------------------
// �`��
//-----------------------------------
void Ranking::Draw()const
{
	SetBackgroundColor(255, 255, 255);
	DrawStringToHandle(58, 113, "No", 0xFFFFFF, menu_font, 0x000000);
	DrawStringToHandle(240, 113, "���O", 0xFFFFFF, menu_font, 0x000000);
	DrawStringToHandle(455, 113, "�X�R�A", 0xFFFFFF, menu_font, 0x000000);

	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatStringToHandle(60, 160 + i * 50, color, menu_font, "%2d", g_Ranking[i].no);
		DrawFormatStringToHandle(120, 160 + i * 50, color, menu_font, "%9s", g_Ranking[i].name);
		DrawFormatStringToHandle(455, 160 + i * 50, color, menu_font, "%5d", g_Ranking[i].score);
	}

	DrawFormatStringToHandle(120, 60, 0xFFFFFF, menu_font, "�����L���O�ɓo�^���܂�");
	DrawFormatStringToHandle(65, 110, 0xFFFFFF, menu_font, "���O���p���œ��͂��Ă�������");
	DrawString(180, 420, "---- START�{�^���������Ė��O����I ----", 0xFFD700, 0);

	DrawFormatStringToHandle(120, 60, 0xFFFFFF, menu_font, "�����L���O�ɓo�^���܂�");
	DrawFormatStringToHandle(65, 110, 0xFFFFFF, menu_font, "���O���p���œ��͂��Ă�������");

	DrawString(180, 420, "---- START�{�^���������Ė��O����I ----", 0xFFD700, 0);

	// ���O�̓���
	DrawFormatStringToHandle(120, 200, 0xFFFFFF, menu_font, "> ");
	DrawBox(190, 200, 425, 250, 0x000055, TRUE);

	DrawFormatStringToHandle(120, 220, 0xff1493, menu_font, "���O����͂��Ă�������");

	for (int i = 0; input_i > i; i++) {
		DrawFormatStringToHandle(195 + i * 25, 205, 0xFFFFFF, menu_font, "%c", buf[i]);
	}
	for (int display = 10; input_i < display; display--) {
		DrawFormatStringToHandle(170 + display * 25, 205, 0xFFFFFF, menu_font, "%c", buf[display - 1]);
	}
	for (int j = 0; j < 5; j++) {
		for (int i = 1; i < 14; i++) {
			if (selecterX + 1 == i && selecterY == j) { DrawFormatString(i * KeyBoard_XMrgin + KeyBoard_X, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", input_char); }
			else { DrawFormatString(i * KeyBoard_XMrgin + KeyBoard_X, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", input_char); }
		}
	}
	DrawCircle(214, 397, 10, 0x000000, 1);
	DrawString(210, 390, "Y", 0xffff00);
	DrawString(234, 390, "�啶���^�������؂�ւ�", 0xFF4500);
	for (int j = 0; j < 4; j++) {
		for (int i = 1; i < 14; i++) {
			if (input_char < '{' || input_char < '[') {
				if (j == 0) {
					if (selecterX + 1 == i && selecterY == j)DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", input_char);
					else { DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", input_char); }
				}
				if (j > 0) {
					if (selecterX + 1 == i && selecterY == j)DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0xff4000, "%c", KeyMap_Qwerty[j - 1][i - 1] + (Uplow == 1 ? 0 : (char)32));
					else {DrawFormatString(i * KEYBORA_XMARGIN + KeyBoard_X + i_space, KEYBORA_Y + KEYBORA_YMARGIN * j, 0x000000, "%c", KeyMap_Qwerty[j - 1][i - 1] + (Uplow == 1 ? 0 : (char)32));
					}
				}
			}
			if (input_char == ':') {
				j = 1; i = 0;
			}
		}
	}

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
	
	FILE* fp;
#pragma warning(disable:4996)
	//�t�@�C���I�[�v��
	fp = fopen("Resource/data/rankingdata.txt", "r");
		
	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < RANKING_DATE; i++) {
		int dammy = fscanf(fp, "%2d %10s %10d", &gRanking[i].no, gRanking[i].name, &gRanking[i].score);
	}

	SetFontSize(48);
	for (int i = 0; i < RANKING_DATE; i++) {
		DrawFormatString(500, 400 + i * 50, 0xffffff,
			"%2d %-10s %10d",
			gRanking[i].no,
			gRanking[i].name,
			gRanking[i].score);
	}
	//DrawStringToHandle(GetDrawCenterX("Science Revenge", title_font), 100, "Science Revenge", 0x66290E, title_font, 0xFFFFFF);
		
}