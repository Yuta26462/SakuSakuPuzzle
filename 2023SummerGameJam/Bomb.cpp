#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb(Cursor* cursor)
{
	this->cursor = cursor;

	//������
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;

	//�e�摜�̓ǂݍ���
	BmImage = LoadGraph("Resource/Images/2-4a/�A�Z�b�g 6.png");
	ExImage = LoadGraph("Resource/Images/Explosion.png");
	
	ExSE = LoadSoundMem("Resource/Sounds/SE/Bomb2.mp3");

	ChangeVolumeSoundMem(400,ExSE);
}

Bomb::~Bomb()
{
	DeleteSoundMem(ExSE);
}

int Bomb::Update()
{
	cursor_pos = cursor->GetMousePos();
	//X�{�^���������ꂽ���c������񐔂��c���Ă��鎞�ɔ��e�I����Ԃ�
	if (state == BOMB_STATE::NOT_SELECT && PAD_INPUT::OnButton(XINPUT_BUTTON_X)&& uses_remaining > 0)
	{
		state = BOMB_STATE::SELECT;
	}

	//���e���I������Ă��鎞�̏���
	if (state == BOMB_STATE::SELECT)
	{
		//�J�[�\�����\���ɂ���
		cursor->SetMouseDisplay(false);

		//A�{�^���������ꂽ��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			//�c��g�p�񐔂����炷
			//uses_remaining--;

			//��Ԃ�"������"�ɂ���
			state = BOMB_STATE::EXPROSION;

			//�������Đ�
			PlaySoundMem(ExSE, DX_PLAYTYPE_BACK);

			//�J�[�\���𓮂��Ȃ��悤�ɂ���
			cursor->SetMouseMove(true);

			//�����G�t�F�N�g�J�n
			bomb_effect = 51;

			//��������
			return true;
		}

		//B�{�^���������ꂽ��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
			//�J�[�\����\������
			cursor->SetMouseDisplay(true);

			//���e���I������Ă����Ԃ���������
			state = BOMB_STATE::NOT_SELECT;
		}
	}

	//���e���������̏���
	if (state == BOMB_STATE::EXPROSION)
	{

		//�G�t�F�N�g�p�ϐ���0�ȉ��ɂȂ�����@
		if (--bomb_effect <= 0)
		{
			//���������甚�e���I������Ă��Ȃ���Ԃɖ߂�
			state = BOMB_STATE::NOT_SELECT;

			//�J�[�\���𓮂��悤�ɂ���
			cursor->SetMouseMove(false);

			//�J�[�\����\������
			cursor->SetMouseDisplay(true);

		}

	}
	//�u���b�N�������s
	return false;
}

void Bomb::Draw()const
{
	switch (state)
	{
	case BOMB_STATE::SELECT:
		//���݂̃J�[�\���̈ʒu�ɔ��e�̉摜��\��
		DrawRotaGraph(cursor_pos.x, cursor_pos.y, 0.25, 0, BmImage, TRUE);
		break;

	case BOMB_STATE::EXPROSION:

		//�G�t�F�N�g�ϐ��̒l�ɉ����Ă��񂾂񓧂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (bomb_effect * 5));

		//���݂̃J�[�\���̈ʒu�ɔ����̉摜��\��
		DrawRotaGraph(cursor_pos.x, cursor_pos.y ,0.25,0,ExImage, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	}
}
void Bomb::Reset()
{
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;
}