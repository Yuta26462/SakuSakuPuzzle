#include "DxLib.h"
#define FADE_TIME 300
#define RANKING_DATE 5
#include "GameMain.h"
#include "PadInput.h"
#include "Title.h"
#include "Ranking.h"

#define FILEPATH "Resource/data/rankingdata.txt"
#define FILEPATH "rankingdata.txt"

RankingData Ranking::Data[RANK];

void Ranking::Insert(int score, char name[NAME_MAX])
{
	ReadRanking();
	if (Data[RANK - 1].score < score)
	{
		Data[RANK - 1].score = score;
		for (int i = 0; i < NAME_MAX; i++)
		{
			Data[RANK - 1].name[i] = name[i];
		}
		SortRanking();
		SaveRanking();
	}
}

void Ranking::SortRanking()
{
	RankingData work;	//並び替え用の変数

	// 選択法ソート
	for (int i = 0; i < RANK - 1; i++) {
		for (int j = i + 1; j < RANK; j++) {
			if (Data[i].score <= Data[j].score) {
				work = Data[i];
				Data[i] = Data[j];
				Data[j] = work;
			}
		}
	}

	// 順位付け
	for (int i = 0; i < RANK; i++) {
		Data[i].no = 1;
	}

	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (int i = 0; i < RANK - 1; i++) {
		for (int j = i + 1; j < RANK; j++) {
			if (Data[i].score > Data[j].score) {
				Data[j].no++;
			}
		}
	}
}

void Ranking::SaveRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, FILEPATH, "w") != NULL)
	{
		throw FILEPATH;
	}

	//ランキングデータを書き込む
	for (int i = 0; i < RANK; i++) {
		fprintf_s(fp, "%1d%10d%10s\n", Data[i].no, Data[i].score, Data[i].name);
	}

	fclose(fp);
}

void Ranking::ReadRanking(void) {
	FILE* fp = NULL;

	//ファイルオープン
	if (fopen_s(&fp, FILEPATH, "r") != NULL)
	{
		throw FILEPATH;
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < RANK; i++) {
		fscanf_s(fp, "%1d%10d%10s", &Data[i].no, &Data[i].score, Data[i].name, NAME_MAX);
	}

	//ファイルクローズ
	fclose(fp);
}
