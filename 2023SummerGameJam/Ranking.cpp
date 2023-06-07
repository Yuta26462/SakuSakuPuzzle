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
	    int i, j;
		
		Ranking::RankingData work = {};
		// �I��@�\�[�g
		for (i = 0; i < RANKING_DATE - 1; i++) {
			for (j = i + 1; j < RANKING_DATE; j++) {
				if (gRanking[i].score <= gRanking[j].score) {
					work = gRanking[i];
					gRanking[i] = gRanking[j];
					gRanking[j] = work;
				}
			}
		}
		// ���ʕt��
		for (i = 0; i < RANKING_DATE; i++) {
			gRanking[i].no = 1;
		}
		// ���_�������ꍇ�́A�������ʂƂ���
		// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
		for (i = 0; i < RANKING_DATE - 1; i++) {
			for (j = i + 1; j < RANKING_DATE; j++) {
				if (gRanking[i].score > gRanking[j].score) {
					gRanking[j].no++;
				}
			}
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