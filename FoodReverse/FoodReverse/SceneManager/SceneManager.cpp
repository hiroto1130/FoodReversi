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
		break;
	case SceneName::ModeSelectScene:
		scene = new ModeSelectScene();
		break;
	case SceneName::SkinSelectScene:
		scene = new SkinSelectScene();
		break;
	case SceneName::GameScene:
		scene = new GameScene();
		break;
	case SceneName::ResultScene:
		scene = new ResultScene();
		break;
	default:
		break;
	}

}

void SceneManager::SceneUpdate()
{
	scene->Update();
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
}
