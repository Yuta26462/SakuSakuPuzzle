#include "InputRankingScene.h"
#include "DrawRanking.h"
#include "PadInput.h"
#include <DxLib.h>

InputRankingScene::InputRankingScene(int _score)
{
	Score = _score;
	XOnce = TRUE;
	YOnce = TRUE;
	CursorPoint = { 0, 0 };
	ranking.ReadRanking();

	//�t�H���g�ǉ�
	NameFont1 = LoadFontDataToHandle("Resource/Fonts/funwari-round.dft");


	//�摜�Ǎ�
	Img = LoadGraph("Resource/Images/Scene/title.png");
}

InputRankingScene::~InputRankingScene()
{
	DeleteFontToHandle(NameFont1);




}

AbstractScene* InputRankingScene::Update()
{
	//�J�[�\������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_UP) || (PAD_INPUT::GetLStick().y > 10000 && YOnce == TRUE)) {

		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		if (--CursorPoint.y < 0) {
			if (CursorPoint.x == 10) {
				CursorPoint.y = 3;
			}
			else {
				CursorPoint.y = 4;
			}
			if (CursorPoint.x == 12) {
				CursorPoint.x = 11;
			}
		}
	}

	//�J�[�\�������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (PAD_INPUT::GetLStick().y < -10000 && YOnce == TRUE)) {

		//�A�����͂��Ȃ��悤�ɂ���
		YOnce = FALSE;

		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		if (++CursorPoint.y > 3 && CursorPoint.x == 10 || CursorPoint.y > 4) {
			CursorPoint.y = 0;
		}
		if (CursorPoint.y > 3 && CursorPoint.x == 12) {
			CursorPoint.x = 11;
		}

	}

	//�J�[�\�����E�ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_RIGHT) || (PAD_INPUT::GetLStick().x > 10000 && XOnce == TRUE)) {

		//�A�����͂��Ȃ��悤�ɂ���
		XOnce = FALSE;

		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		if (++CursorPoint.x == 10 && CursorPoint.y > 3)
		{
			CursorPoint.x = 11;
		}
		if (CursorPoint.x > 11 && CursorPoint.y == 4) {
			CursorPoint.x = 0;
		}
		if (CursorPoint.x > 12) {
			CursorPoint.x = 0;
		}
	}

	//�J�[�\�������ړ�������
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_DPAD_LEFT) || (PAD_INPUT::GetLStick().x < -10000 && XOnce == TRUE)) {

		//�A�����͂��Ȃ��悤�ɂ���
		XOnce = FALSE;

		//�J�[�\�����͂ݏo�Ȃ��悤�ɒ�������
		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--CursorPoint.x < 0) {
			if (CursorPoint.y > 3) {
				CursorPoint.x = 11;
			}
			else {
				CursorPoint.x = 12;
			}
		}
		if (CursorPoint.x == 10 && CursorPoint.y == 4)
		{
			CursorPoint.x = 9;
		}
	}

	//A�{�^���������ꂽ��
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {

		//PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);

		//�m��{�^���������ꂽ��
		if (CursorPoint.x == 11 && CursorPoint.y == 4)
		{
			//���O��1�����ł����͂���Ă�����
			if (Name.size() > 0)
			{
				//�����L���O���X�V����
				Ranking::Insert(Score, const_cast<char*>(Name.c_str()));

				//�����L���O��`�悷��
				//PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
				return new DrawRanking;
			}
		}
		//���O��9�����ȏ���͂���Ă��Ȃ��Ȃ�
		else if (Name.size() < NAME_MAX - 1)
		{
			//���O����͂���
			Name += KeyBoard[CursorPoint.y][CursorPoint.x];
		}
	}

	//B�{�^����������Ė��O��1�����ȏ���͂���Ă���Ȃ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_B) && Name.size() > 0) {
		//���O��1��������
		//PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		Name.erase(Name.begin() + (Name.size() - 1));
	}

	//1�����ȏ���͂���Ă���Start�{�^���������ꂽ�Ȃ�
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START) && Name.size() > 0)
	{
		//�����L���O���X�V����
		Ranking::Insert(Score, const_cast<char*>(Name.c_str()));

		//�����L���O��`�悷��
		PlaySoundMem(DecisionSE, DX_PLAYTYPE_BACK);
		return new DrawRanking;
	}

	//L�X�e�B�b�N��X���W�����̈ʒu�ɖ߂�����t���O�����Z�b�g����
	if (PAD_INPUT::GetLStick().x < 10000 && PAD_INPUT::GetLStick().x > -10000 && XOnce == FALSE) {
		XOnce = TRUE;
	}
	//L�X�e�B�b�N��Y���W�����̈ʒu�ɖ߂�����t���O�����Z�b�g����
	if (PAD_INPUT::GetLStick().y < 10000 && PAD_INPUT::GetLStick().y > -10000 && YOnce == FALSE) {
		YOnce = TRUE;
	}
	return this;
}

void InputRankingScene::Draw() const {

	DrawGraph(0, 0, Img, TRUE);

	DrawStringToHandle(GetDrawCenterX("�Ȃ܂��ɂイ��傭", NameFont1), 100, "�Ȃ܂��ɂイ��傭", 0xffffff, NameFont1);
	
	DrawBox(615, 240, 1365, 350, 0xffffff, TRUE);
	DrawFormatStringToHandle(640, 250, 0x000000, NameFont1, "%s", Name.c_str());

	//�m��̃J�[�\�������傫������
	if (CursorPoint.x == 11 && CursorPoint.y == 4)
	{
		DrawBox(308 + 85 * CursorPoint.x, 353 + 85 * CursorPoint.y,
			458 + 85 * CursorPoint.x, 440 + 85 * CursorPoint.y, 0x808080, TRUE);
		//�h�m��h�̕����F��ς���
		DrawStringToHandle(1250, 705, "OK", 0x000000, NameFont1);
	}
	else
	{
		DrawBox(308 + 85 * CursorPoint.x, 353 + 85 * CursorPoint.y,
			383 + 85 * CursorPoint.x, 430 + 85 * CursorPoint.y, 0x808080, TRUE);
		//���ʂ̕����F�́h�m��h��`�悷��
		DrawStringToHandle(1250, 705, "OK", 0xffffff, NameFont1);
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == CursorPoint.x && i == CursorPoint.y) {
				//I�Ai�AL�̕����̋󔒂𒲐�����
				if (i == 0 && j == 8 && KeyBoard[0][8] || i == 2 && j == 8 && KeyBoard[2][8] || i == 2 && j == 11 && KeyBoard[2][11]) {
					DrawFormatStringToHandle(j * 85 + 328, i * 85 + 355, 0x000000, NameFont1, "%c", KeyBoard[i][j]);
				}
				//g�̕��������𒲐�����
				else if (i == 2 && j == 6 && KeyBoard[0][8]) {
					DrawFormatStringToHandle(j * 85 + 318, i * 85 + 348, 0x000000, NameFont1, "%c", KeyBoard[i][j]);
				}
				else
				{
					DrawFormatStringToHandle(j * 85 + 318, i * 85 + 355, 0x000000, NameFont1, "%c", KeyBoard[i][j]);
				}
			}
			else
			{
				//I�Ai�AL�̕����̋󔒂𒲐�����
				if (i == 0 && j == 8 && KeyBoard[0][8] || i == 2 && j == 8 && KeyBoard[2][8] || i == 2 && j == 11 && KeyBoard[2][11]) {
					DrawFormatStringToHandle(j * 85 + 328, i * 85 + 355, 0xffffff, NameFont1, "%c", KeyBoard[i][j]);
				}
				//g�̕��������𒲐�����
				else if (i == 2 && j == 6 && KeyBoard[0][8]) {
					DrawFormatStringToHandle(j * 85 + 318, i * 85 + 348, 0xffffff, NameFont1, "%c", KeyBoard[i][j]);
				}
				else
				{
					DrawFormatStringToHandle(j * 85 + 318, i * 85 + 355, 0xffffff, NameFont1, "%c", KeyBoard[i][j]);
				}

			}

		}
	}
	DrawStringToHandle(GetDrawCenterX("START�{�^�� or OK�ł����Ă�", NameFont1), 840, "START�{�^�� or OK�ł����Ă�", 0xffffff, NameFont1);
}
