#pragma once
#include "Cursor.h"
//#include "BlockManager.h"
// �u���b�N�̃T�C�Y
const int BLOCK_SIZE = 90;

class Block
{
private:/*
    Cursor::POSITION cursor_pos;*/
    Cursor* cursor;

public:

    int x, y; // �u���b�N�̈ʒu
    int xp, yp; // �u���b�N�̈ʒu
    int shape; // �u���b�N�̌`��i0: �����`, 1: �O�p�`�j
    int rotation; // �u���b�N�̉�]�i0: 0�x, 1: 90�x, 2: 180�x, 3: 270�x�j

    int mx, my;//�ړ��p
    //int cx, cy;//�J�[�\���̈ʒu

  // int MoveFlg=0;

    //int blockimg[6];




    int CompBlock[1][4][4] = { 0 };	//����{�A�e�u���b�N�p

    int PartsBlock[1][4][4] = { 0 };	//�p�[�c�̃u���b�N�p

    int MoveBlock[1][4][4] = { 0 };



public:

    Block() = default;
    //�����L��R���X�g���N�^
    Block(Cursor * cursor);
    //�f�X�g���N�^
    ~Block();

    void Draw();
    void Drawp();
    void Mx(int& x);
    void My(int& y);/*
    void Getc(Cursor::POSITION* cursor);*/
    void Update();

    void flg(int Moveflg);

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

