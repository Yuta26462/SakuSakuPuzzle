#pragma once

// �u���b�N�̃T�C�Y
const int BLOCK_SIZE = 80;

class Block
{
public:
    int x, y; // �u���b�N�̈ʒu
    int shape; // �u���b�N�̌`��i0: �����`, 1: �O�p�`�j
    int rotation; // �u���b�N�̉�]�i0: 0�x, 1: 90�x, 2: 180�x, 3: 270�x�j

public:
    void Draw();

    void rotate() {
        rotation = (rotation + 1) % 4;
    }
};

