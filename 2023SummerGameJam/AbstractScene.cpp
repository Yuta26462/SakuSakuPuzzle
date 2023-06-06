#include "AbstractScene.h"
#include "DxLib.h"

AbstractScene::~AbstractScene()
{
	DeleteFontToHandle(title_font);
}

int AbstractScene::GetDrawCenterX(const char* string, int font_handle)const
{

	//画面幅
	const int screenX = 1920;

	const int w = screenX / 2 - GetDrawFormatStringWidthToHandle(font_handle, string) / 2;
	return w;
}