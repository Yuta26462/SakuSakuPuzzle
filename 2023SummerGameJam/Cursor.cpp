#include "Cursor.h"
#include"PadInput.h"

void CursorInit(void)
{
	int flg;		//使用フラグ（使用中か）
	int x, y;		//座標
	int w, h;		//幅・高さ
	int speed;		//移動速度
};

static Stick l_stick; //左スティック

void PlayerControl(void)
{

	// 移動
	if (l_stick.x) gCursor.x -= gCursor.speed;
	if (l_stick.y) gCursor.x += gCursor.speed;

	// 移動制限
	if (gCursor.x < 3) gCursor.x = 3;
	if (gCursor.x > 1280 - 383) gCursor.x = 1280 - 383;



	DrawString(gCursor.x, gCursor.y, "↑", 0xffffff);
}