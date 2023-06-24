#include "SceneManager.h"



//-----------------------------------
// 更新
//-----------------------------------
AbstractScene* SceneManager::Update()
{

	AbstractScene* NextScene;

	NextScene = mScene->Update();

	if (NextScene != mScene)
	{
		delete mScene;
		mScene = NextScene;
	}

	return mScene;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
SceneManager::~SceneManager()
{

	delete mScene;

}

//-----------------------------------
// 描画
//-----------------------------------
void SceneManager::Draw() const
{

	mScene->Draw();
}
