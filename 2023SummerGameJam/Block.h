#pragma once

//#include "BlockManager.h"
// �u���b�N�̃T�C�Y
const int BLOCK_SIZE = 90;

class Block
{   
private:

public:

    int x, y; // �u���b�N�̈ʒu
    int xp, yp; // �u���b�N�̈ʒu
    int shape; // �u���b�N�̌`��i0: ����, 1: �����`, 2: �O�p�`�j
    int rotation; // �u���b�N�̉�]�i0: 0�x, 1: 90�x, 2: 180�x, 3: 270�x�j

    int mx, my;//�ړ��p
    bool is_hold;   // �͂܂�Ă���t���O
    bool is_empty;

    //int blockimg[6];



public:

    Block();
    
    //�f�X�g���N�^
    ~Block();

    void Draw(int blockimg[6]);
    void Drawp(int blockimg[6]);
    void Update();

    void flg(int Moveflg);//A�{�^���������ꂽ���m�F
    void Hit(int Hitblock);//A�{�^���������ꂽ���m�F

    void rotate();
    //{
    //   // rotation = (rotation + 1) % 4;
    //}
};

