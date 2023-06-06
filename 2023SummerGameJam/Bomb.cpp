#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb()
{
	//������
	uses_remaining = 1;
	bomb_effect = 0;
}

Bomb::~Bomb()
{

}

int Bomb::Update()
{
	//���e���I������Ă��違�c������񐔂��c���Ă��鎞��
	if (state == BOMB_STATE::SELECT && uses_remaining > 0)
	{
		//A�{�^���������ꂽ��
		if (PAD_INPUT::OnPressed(KEY_INPUT_A))
		{
			//�c��g�p�񐔂����炷
			uses_remaining--;
			//��Ԃ�"������"�ɂ���
			state = BOMB_STATE::EXPROSION;
			//�����G�t�F�N�g�J�n
			bomb_effect = 30;
			//��������
			return true;
		}

		//B�{�^���������ꂽ��
		if (PAD_INPUT::OnPressed(KEY_INPUT_B))
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
	switch (state)
	{
	case BOMB_STATE::SELECT:
		//���݂̃J�[�\���̈ʒu�ɔ��e�̉摜��\��
		
		break;
	case BOMB_STATE::EXPROSION:
		//�G�t�F�N�g�ϐ��̒l�ɉ����Ă��񂾂񓧂��Ă���
		
		//���݂̃J�[�\���̈ʒu�ɔ����̉摜��\��

		break;
	}
}