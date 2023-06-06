#include"Bomb.h"
#include"PadInput.h"

Bomb::Bomb()
{
	//初期化
	uses_remaining = 1;
	bomb_effect = 0;
}

Bomb::~Bomb()
{

}

int Bomb::Update()
{
	//爆弾が選択されている＆残り消去回数が残っている時に
	if (state == BOMB_STATE::SELECT && uses_remaining > 0)
	{
		//Aボタンが押されたら
		if (PAD_INPUT::OnPressed(KEY_INPUT_A))
		{
			//残り使用回数を減らす
			uses_remaining--;
			//状態を"爆発中"にする
			state = BOMB_STATE::EXPROSION;
			//爆発エフェクト開始
			bomb_effect = 30;
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
		
		break;
	case BOMB_STATE::EXPROSION:
		//エフェクト変数の値に応じてだんだん透けていく
		
		//現在のカーソルの位置に爆発の画像を表示

		break;
	}
}