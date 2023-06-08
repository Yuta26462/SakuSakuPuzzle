#include "Cursor.h"
#include "PadInput.h"
#include "DxLib.h"
#include <iostream>

Cursor::Cursor()
{
	mouse_pos = { 0, 0 };
	cursor_image = LoadGraph("Resource/Images/cursor.png");

	is_display = true;
	is_stop = false;
}

Cursor::~Cursor()
{
	DeleteGraph(cursor_image);

	is_display = true;
	is_stop = false;
}

void Cursor::Draw() const
{
	if (is_display == true) {
		
		DrawRotaGraph(mouse_pos.x - 40, mouse_pos.y + 100 , 0.1, 0, cursor_image, TRUE);
	}
}

void Cursor::Update()
{
	if (is_stop == true) {
		SetMousePoint(mouse_pos.x, mouse_pos.y);
		return;
	}

	// カーソルの移動速度
	const float speed = 0.5f;

	// スティックの感度
	const int stick_sensitivity = 1500;

	// マウスカーソルの座標を取得・更新
	GetMousePoint(&mouse_pos.x, &mouse_pos.y);

	// 左アナログスティックの座標を取得
	Stick stick_pos;
	stick_pos = PAD_INPUT::GetLStick();


	// 左アナログスティックの座標を出力
	//printfDx("x:%d y:%d\n", stick_pos.x, stick_pos.y);

	if (std::abs(stick_pos.x) > stick_sensitivity || std::abs(stick_pos.y) > stick_sensitivity) {

		stick_pos.x /= static_cast<int>(1000 / speed);
		stick_pos.y /= static_cast<int>(1000 / speed);

		// マウスカーソルの位置をスティックの座標に設定
		SetMousePoint(mouse_pos.x + stick_pos.x, mouse_pos.y + -stick_pos.y);
	}

	//printfDx("x:%d y:%d\n", mouse_pos.x, mouse_pos.y);
}
