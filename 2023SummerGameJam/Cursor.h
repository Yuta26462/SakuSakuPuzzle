
	//�����l�̒萔
	const int Cursor_X = 1000 / 2;
	const int Cursor_Y = 720 - 200;

	struct Cursor
	{
		int flg;		//�g�p�t���O�i�v���C���[���g�p�����j
		int x, y;		//���W
		int w, h;		//���E����
		int speed;		//�ړ����x
	};

	extern Cursor gCursor;
	void CursorInit(void);