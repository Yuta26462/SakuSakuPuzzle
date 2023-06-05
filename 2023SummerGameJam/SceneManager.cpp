#include"DxLib.h"
#include<time.h>
#include "SceneManager.h"

AbstractScene* SceneManager::Update()
{
	AbstractScene* NextScene;
	try
	{
		NextScene = mScene->Update();
	}
	catch (const char* err)
	{
		FILE* fp = NULL;

		DATEDATA data;

		GetDateTime(&data);

		
		fopen_s(&fp, "data/ErrLog/ErrLog.txt", "a");
		
		fprintf_s(fp, "%02d�N %02d�� %02d�� %02d�� %02d�� %02d�b : %s������܂���B\n", data.Year, data.Mon, data.Day, data.Hour, data.Min, data.Sec, err);

		return nullptr;
	}

	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}
	return mScene;
}
void SceneManager::Draw() const
{
	mScene->Draw();
}

