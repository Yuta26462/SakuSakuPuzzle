#include "main.h"
#include "SceneManager.h"
#include "Title.h"
#include "End.h"
#include "PadInput.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	double dNextTime = GetNowCount();

	SetMainWindowText("���������p�Y��");
	SetMainWindowClassName("SakuSakuPuzzle");


	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���

	SetGraphMode(1920, 1080, 32);

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

	SetAlwaysRunFlag(true);		//��ɃA�N�e�B�u�ɂ���

	if (DxLib_Init() == -1)return -1;	

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* sceneMng;

	sceneMng = new SceneManager((AbstractScene*)new Title());

	// �Q�[�����[�v
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {


		ClearDrawScreen();		// ��ʂ̏�����
		PAD_INPUT::UpdateKey();	//�p�b�h�̓��͏�Ԃ̍X�V
		sceneMng->Draw();

		ScreenFlip();			// ����ʂ̓�e��\��ʂɔ��f
		SetWindowVisibleFlag(TRUE);// �E�B���h�E��\��������

		//�t���[�����[�g�̐ݒ�
		dNextTime += static_cast<double>(1.0 / 60.0 * 1000.0);
		if (dNextTime > GetNowCount()) {
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//�␳


	}

	InitFontToHandle();	//�S�Ẵt�H���g�f�[�^��폜
	InitGraph();		//�ǂݍ��񂾑S�ẴO���t�B�b�N�f�[�^��폜
	InitSoundMem();		//�ǂݍ��񂾑S�ẴT�E���h�f�[�^��폜
	DxLib_End();
	return 0;
}