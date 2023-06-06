#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb()
{
	//初期化
	uses_remaining = 1;
	bomb_effect = 0;
	state = BOMB_STATE::NOT_SELECT;

	//爆発画像の読み込み
	if ((ExImage = LoadGraph("Resource/Images/Explosion.png")) == -1)
	{
		throw "Resource/Images/Explosion.png";
	}
}

Bomb::~Bomb()
{

}

int Bomb::Update()
{
	//Xボタンが押された＆残り消去回数が残っている時に爆弾選択状態へ
	if (state == BOMB_STATE::NOT_SELECT && PAD_INPUT::OnPressed(KEY_INPUT_X) && uses_remaining > 0)
	{
		state == BOMB_STATE::SELECT;
	}

	//爆弾が選択されている時の処理
	if (state == BOMB_STATE::SELECT)
	{
		//Aボタンが押されたら
		if (PAD_INPUT::OnPressed(KEY_INPUT_A))
		{
			//残り使用回数を減らす
			uses_remaining--;
			//状態を"爆発中"にする
			state = BOMB_STATE::EXPROSION;
			//爆発エフェクト開始
			bomb_effect = 51;
			//消去成功
			return true;
		}

		//Bボタンが押されたら
		if (PAD_INPUT::OnPressed(KEY_INPUT_B))
		{
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
		DrawString(cursor_x, cursor_y, "ばくだん", 0xff0000);
		break;

	case BOMB_STATE::EXPROSION:

		//エフェクト変数の値に応じてだんだん透けていく
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (bomb_effect * 5));

		//現在のカーソルの位置に爆発の画像を表示
		DrawGraph(cursor_x, cursor_y, ExImage, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		break;
	}
}

void Bomb::SelectBomb() 
{ 
	state = BOMB_STATE::SELECT;
}

void Bomb::SetPos(int x, int y)
{
	cursor_x = x;
	cursor_y = y;
}