#pragma once

// �u���b�N�̃T�C�Y
const int BLOCK_SIZE = 90;

class Block
{
public:
    int x, y; // �u���b�N�̈ʒu
    int xp, yp; // �u���b�N�̈ʒu
    int shape; // �u���b�N�̌`��i0: �����`, 1: �O�p�`�j
    int rotation; // �u���b�N�̉�]�i0: 0�x, 1: 90�x, 2: 180�x, 3: 270�x�j


    //int blockimg[6];




    int CompBlock[1][4][4] = { 0 };	//����{�A�e�u���b�N�p

    int PartsBlock[1][4][4] = { 0 };	//���̃u���b�N�p


public:
    Block();
    ~Block();
    void Draw();

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

