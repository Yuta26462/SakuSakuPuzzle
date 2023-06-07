#pragma once
#include"Cursor.h"

enum class BOMB_STATE {
	NOT_SELECT = 0,	//���e���I������Ă��Ȃ�
	SELECT,			//���e���I������Ă���
	EXPROSION		//������
};

class Bomb{
private:
	int uses_remaining;	//�c��d�l��
	BOMB_STATE state;	//���
	Cursor::POSITION cursor_pos;

	Cursor* cursor;
	
	int BmImage;		//���e�摜
	int ExImage;		//�����摜

	int bomb_effect;	//�����A�j���[�V�����p
public:

	Bomb() = default;

	//�����L��R���X�g���N�^
	Bomb(Cursor* cursor);

	//�f�X�g���N�^
	~Bomb();

	//�`��ȊO�̍X�V�����s
	int Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw()const;

	//��Ԃ��擾����
	BOMB_STATE GetState(){ return state; }

};
