#include "Cursor.h"
#include"PadInput.h"

void CursorInit(void)
{
	int flg;		//�g�p�t���O�i�g�p�����j
	int x, y;		//���W
	int w, h;		//���E����
	int speed;		//�ړ����x
};

static Stick l_stick; //���X�e�B�b�N

void PlayerControl(void)
{

	// �ړ�
	if (l_stick.x) gCursor.x -= gCursor.speed;
	if (l_stick.y) gCursor.x += gCursor.speed;

	// �ړ�����
	if (gCursor.x < 3) gCursor.x = 3;
	if (gCursor.x > 1280 - 383) gCursor.x = 1280 - 383;



	DrawString(gCursor.x, gCursor.y, "��", 0xffffff);
}