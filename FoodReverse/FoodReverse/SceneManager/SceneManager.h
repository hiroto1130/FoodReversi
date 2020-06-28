#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Scene/SceneBase.h"

class SceneManager
{
public:

	SceneManager(SceneName name) { Initialize(name); }

	void CreateScene(SceneName name);

	void SceneUpdate();

	void SceneDrow();

	bool IsSceneChange();

private:

	void Initialize(SceneName name);

	void Delete();

	SceneBase* scene = nullptr;

	SceneName currentScene = SceneName::TitleScene;




};

#endif
