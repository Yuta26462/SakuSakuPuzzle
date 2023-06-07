#pragma once

class AbstractScene
{
protected:

	//�w�i�摜
	int background_image;

	//�w�i���y
	int background_music;

	int cursor_move_se;
	int enter_se;

	int title_bgm;

	int title_font;

	//�X�e�[�W�ԍ�
	short stage_num = 0;

public:

	//�f�X�g���N�^
	virtual ~AbstractScene();

	//�`��ȊO�̍X�V����s
	virtual AbstractScene* Update() = 0;

	//�`��Ɋւ��邱�Ƃ����
	virtual void Draw() const = 0;

	int GetDrawCenterX(const char* string, int font_handle)const;
};