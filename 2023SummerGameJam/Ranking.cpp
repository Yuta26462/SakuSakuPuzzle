#include "Ranking.h"
#include "DxLib.h"
#define FADE_TIME 300
#define RANKING_DATE 5
#include "GameMain.h"
#include "PadInput.h"
#include "Title.h"

Ranking::RankingData  gRanking[RANKING_DATE];

//-----------------------------------
// コンストラクタ
//-----------------------------------
Ranking::Ranking()
{

	menu_font = CreateFontToHandle("メイリオ", 60, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, 4);

	background_image = LoadGraph("Resource/Images/Scene/title.png");

	//if ((background_music = LoadSoundMem("Sounds/BGM/Title.wav")) == -1) {
	//	throw "Sounds/BGM/Title.wav";
	//}

	//if ((enter_se = LoadSoundMem("Resource/Sounds/SE/enter.mp3")) == -1) {
	//	throw "Resource/Sounds/SE/enter.mp3";
	//}

	//if ((cursor_move_se = LoadSoundMem("Resource/Sounds/SE/cursor_move.mp3")) == -1)
	//{
	//	throw "Resource/Sounds/SE/cursor_move.mp3";
	//}
	 //構造体

	//struct RankingData {
		//int		no;
		//char	name[11];
		//long	score;
	//};

	//constexpr auto RANKING_DATA = 5;	//ランキングデータの数;

	//RankingData gRanking[RANKING_DATA]{};

	//struct RankingData		gRanking[RANKING_DATA]{};

	//char MoziSmall[] = "abcdefghijklmnopqrstuvwxyz";
	//char MoziBig[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//char MoziNumber[] = "0123456789";

	//char MoziFrame[11]{};
	///char MoziWork[2]{};

	select_se = 0;
	decision_se = 0;

	input_margin = 0;

#ifdef TITLE_DEBUG
	is_select_debug = false;
#endif // TITLE_DEBUG


	select_menu = static_cast<int>(MENU::PLAY);

	fade_counter = 0;

	//PlaySoundMem(background_music, DX_PLAYTYPE_LOOP, FALSE);

}

//-----------------------------------
// デストラクタ
//-----------------------------------
Ranking::~Ranking()
{
	//DeleteGraph(background_image);
	//StopSoundMem(background_music);
	//DeleteSoundMem(background_music);
	//DeleteSoundMem(enter_se);
	//DeleteSoundMem(cursor_move_se);
	//DeleteFontToHandle(title_font);
	DeleteFontToHandle(menu_font);
	SetDrawBright(255, 255, 255);
}

//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* Ranking::Update()
{
	if (fade_counter < FADE_TIME)
	{
		fade_counter++;
	}

#ifndef TITLE_DEBUG
	if (fade_counter < FADE_TIME)
	{

	}
#endif // !TITLE_DEBUG

	// 操作間隔時間
	const int max_input_margin = 15;

	// スティックの感度
	const int stick_sensitivity = 20000;

	if (input_margin < max_input_margin)
	{
		input_margin++;
	}
	else {

		// スティックのY座標を取得
		//int stick_y = PAD_INPUT::GetLStick().y;

		//if (std::abs(stick_y) > stick_sensitivity) {

		//	PlaySoundMem(cursor_move_se, DX_PLAYTYPE_BACK, TRUE);

		//	// スティックが上に移動した場合
		//	if (stick_y > 0) {
		//		// メニュー選択肢を一つ前に移動
		//		select_menu = (select_menu - 1 + static_cast<int>(MENU::MENU_SIZE)) % static_cast<int>(MENU::MENU_SIZE);
		//	}
		//	// スティックが下に移動した場合
		//	else if (stick_y < 0) {
		//		// メニュー選択肢を一つ次に移動
		//		select_menu = (select_menu + 1) % static_cast<int>(MENU::MENU_SIZE);
		//	}

		//	input_margin = 0;

		//}

	}

	//
	//	if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == true))
	//	{
	//
	//		PlaySoundMem(enter_se, DX_PLAYTYPE_BACK, TRUE);
	//		while (CheckSoundMem(enter_se)) {}
	//
	//#ifdef TITLE_DEBUG
	//		if (is_select_debug == true) {
	//			return new DotByDot();
	//		}
	//#endif // TITLE_DEBUG
	//
	//
	//		input_margin = 0;
	//		MENU current_selection = static_cast<MENU>(select_menu);
	//
	//		switch (current_selection)
	//		{
	//		case Title::MENU::PLAY:
	//			return new GameMain(1, element_volume, pouch);
	//			break;
	//
	//		case Title::MENU::HELP:
	//		{
	//			GameMain* help = new GameMain(0, element_volume, pouch);
	//			help->SetHelpMode(true);
	//			return help;
	//			break;
	//		}
	//		case Title::MENU::EXIT:
	//			return new Credit();
	//			break;
	//
	//		default:
	//			printfDx("未実装な機能です。\n");
	//			break;
	//		}
	//
	//	}
	if (PAD_INPUT::OnPressed(XINPUT_BUTTON_A)) {
		return new Title();
	}

	return this;
}

int Ranking::ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)
	//ファイルオープン
	if ((fp = fopen("Resource/data/rankingdata.txt", "r")) == NULL) {
		//エラー処理

		printf("Ranking Data Error\n");
		return -1;
	}
	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANKING_DATE; i++) {
		int dammy = fscanf(fp, "%2d %10s %10d", &gRanking[i].no, gRanking[i].name, &gRanking[i].score);
	}
	return 0;
}

//-----------------------------------
// 描画
//-----------------------------------
void Ranking::Draw()const
{
	    int i, j;
		
		Ranking::RankingData work = {};
		// 選択法ソート
		for (i = 0; i < RANKING_DATE - 1; i++) {
			for (j = i + 1; j < RANKING_DATE; j++) {
				if (gRanking[i].score <= gRanking[j].score) {
					work = gRanking[i];
					gRanking[i] = gRanking[j];
					gRanking[j] = work;
				}
			}
		}
		// 順位付け
		for (i = 0; i < RANKING_DATE; i++) {
			gRanking[i].no = 1;
		}
		// 得点が同じ場合は、同じ順位とする
		// 同順位があった場合の次の順位はデータ個数が加算された順位とする
		for (i = 0; i < RANKING_DATE - 1; i++) {
			for (j = i + 1; j < RANKING_DATE; j++) {
				if (gRanking[i].score > gRanking[j].score) {
					gRanking[j].no++;
				}
			}
		}
	
	FILE* fp;
#pragma warning(disable:4996)
	//ファイルオープン
	fp = fopen("Resource/data/rankingdata.txt", "r");
		
	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANKING_DATE; i++) {
		int dammy = fscanf(fp, "%2d %10s %10d", &gRanking[i].no, gRanking[i].name, &gRanking[i].score);
	}

	SetFontSize(48);
	for (int i = 0; i < RANKING_DATE; i++) {
		DrawFormatString(500, 400 + i * 50, 0xffffff,
			"%2d %-10s %10d",
			gRanking[i].no,
			gRanking[i].name,
			gRanking[i].score);
	}
	//DrawStringToHandle(GetDrawCenterX("Science Revenge", title_font), 100, "Science Revenge", 0x66290E, title_font, 0xFFFFFF);
		
}