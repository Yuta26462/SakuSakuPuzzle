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

	// �}�E�X�J�[�\���̃O���t�B�b�N�n���h��
	int cursor_image;

	// �}�E�X�J�[�\���̍��W
	Cursor::POSITION mouse_pos;

	// �}�E�X�J�[�\���̕\���t���O
	bool is_display;

	// �}�E�X�J�[�\���̒�~�t���O
	bool is_stop;

public:
	Cursor();
	~Cursor();
	void Draw()const;
	void Update();

	
	/// <summary>
	/// �}�E�X�J�[�\���̍��W���擾
	/// </summary>
	/// <returns>Cursor::POSITION�\���̌^�F�}�E�X�J�[�\�����W</returns>
	Cursor::POSITION GetMousePos()const { return mouse_pos; }

	/// <summary>
	/// �}�E�X�J�[�\���̕\���E��\��Setter
	/// </summary>
	/// <param name = "display">bool�^�F�\���E��\��</param>
	void SetMouseDisplay(bool display) { is_display = display; }

	/// <summary>
	/// �}�E�X�J�[�\���̒�~Setter
	/// </summary>
	/// <param name = "num">bool�^�F��~�E�ړ��\</param>
	void SetMouseMove(bool move) { is_stop = move; }
};

