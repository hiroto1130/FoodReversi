#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Scene/SceneBase.h"

class SceneManager
{
public:

	SceneManager(SceneName name) { Initialize(name); }
	~SceneManager() { Delete(); }

	/**
	 * Sceneを作成する関数
	 * @param name 作成するSceneの名前
	 * @detail SceneManagerを呼ぶ際にもInitialize関数で呼ばれる
	 */
	void CreateScene(SceneName name);

	/**
	 * 現在のSceneのUpdate関数をここで呼ぶ
	 */
	void SceneUpdate();
	
	/**
	 * 現在のSceneのDraw関数をここで呼ぶ
	 */
	void SceneDrow();
	
	/**
	 * Sceneが変えるかどうかを確認する関数
	 * @return Sceneが変わるなら true それ以外なら false
	 */
	bool IsSceneChange();

private:

	/**
	 * 初期化関数
	 */
	void Initialize(SceneName name);


	/**
	 * 削除関数
	 * @detail デストラクタで呼び、delete処理をメインで行う
	 */
	void Delete();

	SceneBase* scene = nullptr;

	SceneName currentScene = SceneName::TitleScene;




};

#endif
