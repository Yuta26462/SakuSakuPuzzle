#pragma once

enum class BOMB_STATE {
	NOT_SELECT = 0,	//���e���I������Ă��Ȃ�
	SELECT,			//���e���I������Ă���
	EXPROSION		//������
};

class Bomb{
private:
	int cursor_x, cursor_y;			//�J�[�\���ʒu
	int uses_remaining;	//�c��d�l��
	BOMB_STATE state;	//���

	int BmImage;		//���e�摜
	int ExImage;		//�����摜

	int bomb_effect;	//�����A�j���[�V�����p
public:
	//�R���X�g���N�^
	Bomb();

	//�f�X�g���N�^
	~Bomb();

	//�`��ȊO�̍X�V�����s
	int Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const;

	//���e��I��������Ԃɂ���
	void SelectBomb();

	//�J�[�\���̍��W���擾����
	void SetPos(int x, int y);

	//��Ԃ��擾����
	BOMB_STATE GetState(){ return state; }

};
