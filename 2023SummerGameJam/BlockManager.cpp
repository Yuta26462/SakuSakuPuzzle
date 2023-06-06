#include "BlockManager.h"
#include "DxLib.h"


BlockManager::BlockManager(POSITION posittion)
{
    POSITION sample_posittion = { 200,200};

    // �����̃u���b�N�̐���
    for (int i = 0; i < 6; i++) {
        Block block;
        block.x = i * BLOCK_SIZE + sample_posittion.x;
        block.y = 0 + sample_posittion.y;
        block.shape = GetRand(1); // 0�܂���1�̃����_���Ȓl
        block.rotation = 0;
        sampleBlocks.push_back(block);
    }

    // ����{�̃u���b�N��splitNum�̒l�ɉ����ĕ������A�v���C���[�̃u���b�N�Ƃ��Ċi�[
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
            Block block;
            block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
            block.y = sampleBlock.y + posittion.y;
            block.shape = sampleBlock.shape;
            block.rotation = sampleBlock.rotation;
            playerBlocks.push_back(block);
        }
    }
}


BlockManager::~BlockManager() = default;

void BlockManager::Draw()
{

    // �u���b�N�̕`��
    for (Block& block : sampleBlocks) {
        block.Draw();
    }
    for (Block& block : playerBlocks) {
        block.Draw();
    }
}

void BlockManager::Update()
{
    // �`��̃}�b�`���O�ƃX�R�A�̍X�V
        // TODO: ����{�̃u���b�N�ƃv���C���[�̃u���b�N����v���Ă��邩�m�F���A�X�R�A��X�V

        bool isMatch = false;
    for (int i = 0; i < sampleBlocks.size(); i++) {
        if (sampleBlocks[i].x != playerBlocks[i].x || sampleBlocks[i].y != playerBlocks[i].y ||
            sampleBlocks[i].shape != playerBlocks[i].shape || sampleBlocks[i].rotation != playerBlocks[i].rotation) {
            isMatch = false;
            break;
        }
    }
    if (isMatch) {
        // �X�R�A����Z
        // TODO: �V��������{�̃u���b�N�𐶐�
    }
    // �X�R�A�������邽�тɃu���b�N�̕������𑝂₷

}

void BlockManager::GenerationExsampleBlock()
{
    sampleBlocks.clear();
    playerBlocks.clear();

    POSITION posittion = { 1000,760 };
    POSITION sample_posittion = { 200,200 };

    // �����̃u���b�N�̐���
    for (int i = 0; i < 6; i++) {
        Block block;
        block.x = i * BLOCK_SIZE + sample_posittion.x;
        block.y = 0 + sample_posittion.y;
        block.shape = GetRand(1); // 0�܂���1�̃����_���Ȓl
        block.rotation = 0;
        sampleBlocks.push_back(block);
    }

    // ����{�̃u���b�N��splitNum�̒l�ɉ����ĕ������A�v���C���[�̃u���b�N�Ƃ��Ċi�[
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
            Block block;
            block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
            block.y = sampleBlock.y + posittion.y;
            block.shape = sampleBlock.shape;
            block.rotation = sampleBlock.rotation;
            playerBlocks.push_back(block);
        }
    }

}

void BlockManager::GenerationPlayerBlock()
{
    playerBlocks.clear();
	POSITION posittion = { 1000,760 };
	POSITION sample_posittion = { 200,200 };
	// ����{�̃u���b�N��splitNum�̒l�ɉ����ĕ������A�v���C���[�̃u���b�N�Ƃ��Ċi�[
    for (Block const& sampleBlock : sampleBlocks) {
        for (int i = 0; i < 1; i++) {
			Block block;
			block.x = sampleBlock.x + (i * BLOCK_SIZE / splitNum) + posittion.x;
			block.y = sampleBlock.y + posittion.y;
			block.shape = sampleBlock.shape;
			block.rotation = sampleBlock.rotation;
			playerBlocks.push_back(block);
		}
	}
}

void BlockManager::Split()
{
	// �u���b�N�̕���
}

void BlockManager::Merge()
{
	// �u���b�N�̌���
}

void BlockManager::Rotate()
{
	// �u���b�N�̉�]
    for (Block const& playerBlock : playerBlocks) {
        //playerBlock.rotation(
    }
}

void BlockManager::Move()
{
	// �u���b�N�̈ړ�
}

void BlockManager::Reset()
{
	// �u���b�N�̃��Z�b�g
}

