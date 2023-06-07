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
};

