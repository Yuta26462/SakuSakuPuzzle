#pragma once

class Cursor
{
public:
	struct POSITION
	{
		int x;
		int y;

	};


private:

	// マウスカーソルのグラフィックハンドル
	int cursor_image;

	// マウスカーソルの座標
	Cursor::POSITION mouse_pos;

public:
	Cursor();
	~Cursor();
	void Draw()const;
	void Update();

	
	/// <summary>
	/// マウスカーソルの座標を取得
	/// </summary>
	/// <returns>Cursor::POSITION構造体型：マウスカーソル座標</returns>
	Cursor::POSITION GetMousePos()const { return mouse_pos; }
};

