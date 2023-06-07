#pragma once
#include"Cursor.h"

enum class BOMB_STATE {
	NOT_SELECT = 0,	//爆弾が選択されていない
	SELECT,			//爆弾が選択されている
	EXPROSION		//爆発中
};

class Bomb{
private:
	int uses_remaining;	//残り仕様回数
	BOMB_STATE state;	//状態
	Cursor::POSITION cursor_pos;

	Cursor* cursor;
	
	int BmImage;		//爆弾画像
	int ExImage;		//爆発画像

	int bomb_effect;	//爆発アニメーション用
public:

	Bomb() = default;

	//引数有りコンストラクタ
	Bomb(Cursor* cursor);

	//デストラクタ
	~Bomb();

	//描画以外の更新を実行
	int Update();

	//描画に関することを実装
	void Draw()const;

	//状態を取得する
	BOMB_STATE GetState(){ return state; }

};
