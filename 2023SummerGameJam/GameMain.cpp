#include "GameMain.h"
#include "DxLib.h"

#define FADE_TIME 300

#define Limit 60
#define HEIGHT 9
#define WIDTH 10

int Stage[HEIGHT][WIDTH];
int BlockHome[3][HEIGHT][WIDTH]; //�X�e�[�W�z�� �u���b�N�z�u�\�ӏ�
int backImg;
int blockimg[6];

int BlockFlg = TRUE;

int CompblockList[8][4][4]{

	{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{0,1,1,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{0,4,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,4,3,0},{0,2,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,1,1,0},{0,1,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,3,5,0},{0,2,4,0},{0,0,0,0}},
	{{0,0,0,0},{1,1,1,0},{1,4,5,0},{0,0,0,0}},
	{{0,0,0,0},{0,2,3,0},{2,1,1,3},{0,0,0,0}},
	//�Ђ��`{{0,2,3,0},{2,1,1,3},{4,1,1,5},{0,4,5,0}}
};


int PBlockList[4][4][2]{
	//4�܂�
	{{0,0},{1,1},{1,1},{0,0}},
	{{0,0},{4,1},{2,1},{0,0}},
	{{2,0},{3,0},{4,0},{5,0}},
	{{0,0},{2,5},{5,2},{0,0}},

};

int CompBlock[4][4] = { 0 };	//����{�A�e�u���b�N�p
int PartsBlock[4][4] = { 0 };	//���̃u���b�N�p


int TimeCount = 0;
int Time = 0;
int r = 0;


//-----------------------------------
// �R���X�g���N�^
//-----------------------------------
GameMain::GameMain()
{
	title_font = CreateFontToHandle("���C���I", 90, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 8);

	//menu_font = CreateFontToHandle("���C���I", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/game_main.png");

	block_manager = new BlockManager();
	backImg = LoadGraph("img/backimg.png");
	LoadDivGraph("Resource/Images/2-4a/block.png", 6, 6, 1, 90, 90, blockimg);


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


	//�u���b�N�쐬
	//�V�����u���b�N���Z�b�g�����̃u���b�N�𐶐�
	//��񂾂����悤�ɂ���

	if (BlockFlg == TRUE) {

		BlockFlg = FALSE;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				CompBlock[i][j] = CompblockList[r][i][j];

				//PartsBlock[i][j] = PBlockList[r][i][j];
			}
		}	


		for (int c = 0; c < 2; c++) 
		{
			//i�͍s��������
			//i��PBlockList[r][i][j]�̌��钆�g��������

			for (int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++) 
				{
					BlockHome[c][i][j] = PBlockList[r][i][j];
				}
			}

		}

		
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (CompBlock[i][j] != 0) {
					Stage[i][j] = CompBlock[i][j];
				}
			}
		}


	}



	//��������
	TimeCount++;
	if (TimeCount > 60) {
		TimeCount = 0;
		Time++;
	}

	if (Time > Limit) {
		Time = 0;
	}

		block_manager->Update();

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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	//NEW�u���b�N��`��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <4; j++) {
			if (CompBlock[i][j] != 0) {
				DrawGraph(90 * (j + 11), 90 * (i + 2), blockimg[CompBlock[i][j]], TRUE);
			}
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//����u���b�N��`��
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (CompBlock[i][j] != 0) {
				DrawRotaGraph(72 * (j + 1.2), 72 * (i + 2), 0.8, 0, blockimg[CompBlock[i][j]], TRUE);
			}
		}
	}


	////�p�[�c�u���b�N��\���@���̕�
	for (int c = 0; c < 1; c++) {

		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				if (BlockHome[c][i][j] != 0)
				{
					DrawGraph((j + 6) * 90+(c*250), (i + 10) * 90, blockimg[BlockHome[c][i][j]], TRUE);
				}
			}
		}

	}
		


	SetFontSize(40);
	DrawString(150, 20, "����", 0x000000);
	DrawString(120, 400, "��������", 0x000000);
	DrawFormatString(120, 500, 0x000000, "%d", Time);


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
