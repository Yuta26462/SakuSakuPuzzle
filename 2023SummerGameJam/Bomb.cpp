#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb()
{
	//������
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;
	cursor_x = 100;
	cursor_y = 100;
	//�����摜�̓ǂݍ���
	if ((ExImage = LoadGraph("Resource/Images/Explosion.png")) == -1)
	{
		throw "Resource/Images/Explosion.png";
	}
}

Bomb::~Bomb()
{

}

int Bomb::Update()
{
	//X�{�^���������ꂽ���c������񐔂��c���Ă��鎞�ɔ��e�I����Ԃ�
	if (state == BOMB_STATE::NOT_SELECT && PAD_INPUT::OnButton(XINPUT_BUTTON_X)&& uses_remaining > 0)
	{
		state = BOMB_STATE::SELECT;
	}

	//���e���I������Ă��鎞�̏���
	if (state == BOMB_STATE::SELECT)
	{
		//A�{�^���������ꂽ��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			//�c��g�p�񐔂����炷
			uses_remaining--;
			//��Ԃ�"������"�ɂ���
			state = BOMB_STATE::EXPROSION;
			//�����G�t�F�N�g�J�n
			bomb_effect = 51;
			//��������
			return true;
		}

		//B�{�^���������ꂽ��
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
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
		}
	}
	//�u���b�N�������s
	return false;
}

void Bomb::Draw()const
{
	DrawString(10,10,"bomb",0xff0000);
	switch (state)
	{
	case BOMB_STATE::SELECT:
		//���݂̃J�[�\���̈ʒu�ɔ��e�̉摜��\��
		DrawString(cursor_x, cursor_y, "���e�I��", 0xff0000);
		break;

	case BOMB_STATE::EXPROSION:

		//�G�t�F�N�g�ϐ��̒l�ɉ����Ă��񂾂񓧂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (bomb_effect * 5));

		//���݂̃J�[�\���̈ʒu�ɔ����̉摜��\��
		DrawRotaGraph(cursor_x, cursor_y ,0.5,0,ExImage, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	}
}

void Bomb::SelectBomb() 
{ 
	state = BOMB_STATE::SELECT;
}

void Bomb::SetPos(int x, int y)
{
	cursor_x = x;
	cursor_y = y;
}