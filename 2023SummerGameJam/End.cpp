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
	background_music = LoadSoundMem("Resource/Sounds/BGM/End.mp3");
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


	PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, TRUE);
}

//-----------------------------------
// �f�X�g���N�^
//-----------------------------------
END::~END()
{
	StopSoundMem(background_music);
	DeleteSoundMem(background_music);
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
	}
	
	if (++WaitTime > 400) {
		return nullptr;
	}

	return this;
}

//-----------------------------------
// �`��
//-----------------------------------
void END::Draw()const
{
	int bright = static_cast<int>((static_cast<float>(fade_counter[0]) / FADE_TIME * 255));

	SetDrawBright(bright, bright, bright);

	DrawGraph(0, 0, background_image, FALSE);

	DrawStringToHandle(GetDrawCenterX("�������Ă����傤", title_font), 80, "�������Ă����傤", 0xE1D000, title_font, 0xFFFFFF);

	DrawStringToHandle(GetDrawCenterX("BGM", menu_font), 300, "BGM", 0xff0000, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("���܂ڂ�������", menu_font), 420, "���܂ڂ�������", 0x0000f0, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("yuhei komatsu", menu_font), 520, "yuhei komatsu", 0x0000f0, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("SE", menu_font), 650, "SE", 0xff0000, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("���������񃉃{", menu_font), 780, "���������񃉃{", 0x0000f0, menu_font, 0xFFFFFF);
	DrawStringToHandle(GetDrawCenterX("�Ղꂢ���Ă���Ă��肪�Ƃ�", menu_font), 880, "�Ղꂢ���Ă���Ă��肪�Ƃ�", 0xff0000, menu_font, 0xFFFFFF);

}
