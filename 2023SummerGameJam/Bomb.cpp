#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb(Cursor* cursor)
{
	this->cursor = cursor;

	//初期化
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;

	//各画像の読み込み
	BmImage = LoadGraph("Resource/Images/2-4a/アセット 6.png");
	ExImage = LoadGraph("Resource/Images/Explosion.png");
	
	ExSE = LoadSoundMem("Resource/Sounds/SE/Bomb2.mp3");

	ChangeVolumeSoundMem(400,ExSE);
}

Bomb::~Bomb()
{
	DeleteSoundMem(ExSE);
}

int Bomb::Update()
{
	cursor_pos = cursor->GetMousePos();
	//Xボタンが押された＆残り消去回数が残っている時に爆弾選択状態へ
	if (state == BOMB_STATE::NOT_SELECT && PAD_INPUT::OnButton(XINPUT_BUTTON_X)&& uses_remaining > 0)
	{
		state = BOMB_STATE::SELECT;
	}

	//爆弾が選択されている時の処理
	if (state == BOMB_STATE::SELECT)
	{
		//カーソルを非表示にする
		cursor->SetMouseDisplay(false);

		//Aボタンが押されたら
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_A))
		{
			//残り使用回数を減らす
			//uses_remaining--;

			//状態を"爆発中"にする
			state = BOMB_STATE::EXPROSION;

			//爆発音再生
			PlaySoundMem(ExSE, DX_PLAYTYPE_BACK);

			//カーソルを動かないようにする
			cursor->SetMouseMove(true);

			//爆発エフェクト開始
			bomb_effect = 51;

			//消去成功
			return true;
		}

		//Bボタンが押されたら
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_B))
		{
			//カーソルを表示する
			cursor->SetMouseDisplay(true);

			//爆弾が選択されている状態を解除する
			state = BOMB_STATE::NOT_SELECT;
		}
	}

	//爆弾が爆発中の処理
	if (state == BOMB_STATE::EXPROSION)
	{

		//エフェクト用変数が0以下になったら　
		if (--bomb_effect <= 0)
		{
			//爆発中から爆弾が選択されていない状態に戻る
			state = BOMB_STATE::NOT_SELECT;

			//カーソルを動くようにする
			cursor->SetMouseMove(false);

			//カーソルを表示する
			cursor->SetMouseDisplay(true);

		}

	}
	//ブロック消去失敗
	return false;
}

void Bomb::Draw()const
{
	switch (state)
	{
	case BOMB_STATE::SELECT:
		//現在のカーソルの位置に爆弾の画像を表示
		DrawRotaGraph(cursor_pos.x, cursor_pos.y, 0.25, 0, BmImage, TRUE);
		break;

	case BOMB_STATE::EXPROSION:

		//エフェクト変数の値に応じてだんだん透けていく
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (bomb_effect * 5));

		//現在のカーソルの位置に爆発の画像を表示
		DrawRotaGraph(cursor_pos.x, cursor_pos.y ,0.25,0,ExImage, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	}
}
void Bomb::Reset()
{
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;
}