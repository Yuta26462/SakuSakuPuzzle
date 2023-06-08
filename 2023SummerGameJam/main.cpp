#include "main.h"
#include "SceneManager.h"
#include "Title.h"
#include "PadInput.h"
#include "End.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	double dNextTime = GetNowCount();

	SetMainWindowText("さくさくパズル");
	SetMainWindowClassName("SakuSakuPuzzle");
	SetDXArchiveExtension("resource");
	SetDXArchiveKeyString("map_chips90.png");

	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする

	SetGraphMode(1920, 1080, 32);
	

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);

	SetAlwaysRunFlag(true);		//常にアクティブにする

	if (DxLib_Init() == -1)return -1;	

	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* sceneMng;

	sceneMng = new SceneManager((AbstractScene*)new Title());

	// ゲームループ
	while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {


		ClearDrawScreen();		// 画面の初期化
		PAD_INPUT::UpdateKey();	//パッドの入力状態の更新
		sceneMng->Draw();

		ScreenFlip();			// 裏画面の内容を表画面に反映
		SetWindowVisibleFlag(TRUE);// ウィンドウを表示させる

		//フレームレートの設定
		dNextTime += 1.0 / 60.0 * 1000.0;
		if (dNextTime > GetNowCount()) {
			WaitTimer(static_cast<int>(dNextTime) - GetNowCount());
		}
		else { dNextTime = GetNowCount(); }		//補正


		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}
	}

	InitFontToHandle();	//全てのフォントデータを削除
	InitGraph();		//読み込んだ全てのグラフィックデータを削除
	InitSoundMem();		//読み込んだ全てのサウンドデータを削除
	DxLib_End();
	return 0;
}