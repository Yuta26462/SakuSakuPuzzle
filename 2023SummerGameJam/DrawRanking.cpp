#include "DrawRanking.h"
#include "Ranking.h"
#include "PadInput.h"
#include "Title.h"

DrawRanking::DrawRanking()
{
	Image = LoadGraph("Resource/Images/Scene/title.png");
	//�t�H���g�̒ǉ�
	HeadLineFont =  LoadFontDataToHandle("Resource/Fonts/funwari-round.dft");

	//�����L���O�f�[�^�̓ǂݍ���
	Ranking::ReadRanking();
}

DrawRanking::~DrawRanking()
{
	DeleteFontToHandle(HeadLineFont);
}

AbstractScene* DrawRanking::Update()
{
	//A�{�^���Ń^�C�g����
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
	{
		return new Title();
	}
	return this;
}

void DrawRanking::Draw() const
{
	DrawGraph(0, 0, Image, FALSE);
	DrawStringToHandle(470, 75, "�����L���O", 0xffd800, HeadLineFont);

	int color = 0xffffff;
	for (int i = 0; i < RANK; i++)
	{
		//���ʂɉ����ĕ����F��ς���(1��:��(���F) 2��:��(��F) 3��:��(���F))
		switch (Ranking::GetData(i).no)
		{
		case 1:
			color = 0xc0c0c0;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			color = 0x000000;
			break;
		default:
			break;
		}
		int GetDrawStringWidthToHandle(char* String, int StrLen, int FontHandle);
		DrawFormatStringToHandle(270, 220 + (70 * i), color, HeadLineFont, "%d��", Ranking::GetData(i).no);
		DrawFormatStringToHandle(400, 220 + (70 * i), color, HeadLineFont, "%.10s", Ranking::GetData(i).name);
		DrawFormatStringToHandle(950 - GetDrawFormatStringWidthToHandle(HeadLineFont, "%d", Ranking::GetData(i).score) / 2, 220 + (70 * i), color, HeadLineFont, "%6dpt", Ranking::GetData(i).score);
	}

	DrawStringToHandle(425, 650, "A �Ń^�C�g��", 0xff0000, HeadLineFont);
}
