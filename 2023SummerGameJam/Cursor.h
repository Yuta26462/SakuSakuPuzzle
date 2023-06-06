
	//初期値の定数
	const int Cursor_X = 1000 / 2;
	const int Cursor_Y = 720 - 200;

	struct Cursor
	{
		int flg;		//使用フラグ（プレイヤーが使用中か）
		int x, y;		//座標
		int w, h;		//幅・高さ
		int speed;		//移動速度
	};

	extern Cursor gCursor;
	void CursorInit(void);