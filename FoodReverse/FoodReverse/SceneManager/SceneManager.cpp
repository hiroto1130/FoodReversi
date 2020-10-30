#include "SceneManager.h"

#include "../Scene/Title/Title.h"
#include "../Scene/ModeSelect/ModeSelect.h"
#include "../Scene/SkinSelect/SkinSelect.h"
#include "../Scene/Game/GameScene.h"
#include "../Scene/Result/Result.h"

void SceneManager::CreateScene(SceneName name)
{
	delete scene;
	scene = nullptr;

	switch (name)
	{
	case SceneName::TitleScene:
		scene = new TitleScene();
		currentScene = SceneName::TitleScene;
		// title画面でskin変更をするためここでSkinClassのインスタンスを作成する
		Skin::create();
		break;
	case SceneName::ModeSelectScene: // 削除予定
		scene = new ModeSelectScene();
		currentScene = SceneName::ModeSelectScene;
		break;
	case SceneName::SkinSelectScene:
		scene = new SkinSelectScene();
		currentScene = SceneName::SkinSelectScene;
		break;
	case SceneName::GameScene:
		scene = new GameScene();
		currentScene = SceneName::GameScene;
		break;
	case SceneName::ResultScene: // 削除予定(仕様変更で使う可能性有)
		scene = new ResultScene();
		currentScene = SceneName::ResultScene;
		break;
	default:
		break;
	}

}

void SceneManager::SceneUpdate(Library::Key& key)
{
	scene->Update(key);
}

void SceneManager::SceneDrow()
{
	scene->Draw();
}

void SceneManager::SceneChangeCheck()
{
	if (scene->Exit() != currentScene)
	{
		SceneName nextScene = scene->Exit();

		CreateScene(nextScene);
	}

}

void SceneManager::Initialize(SceneName name)
{
	CreateScene(name);
	currentScene = name;
}

void SceneManager::Delete()
{
	delete scene;
	scene = nullptr;
	// 確定で消すDelete関数でSkinClassのインスタンスも削除する(仮置き)
	Skin::destroy();
}
