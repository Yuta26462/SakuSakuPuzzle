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

	// マウスカーソルの表示フラグ
	bool is_display;

	// マウスカーソルの停止フラグ
	bool is_stop;

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

	/// <summary>
	/// マウスカーソルの表示・非表示Setter
	/// </summary>
	/// <param name = "display">bool型：表示・非表示</param>
	void SetMouseDisplay(bool display) { is_display = display; }

	/// <summary>
	/// マウスカーソルの停止Setter
	/// </summary>
	/// <param name = "num">bool型：停止・移動可能</param>
	void SetMouseMove(bool move) { is_stop = move; }
};

