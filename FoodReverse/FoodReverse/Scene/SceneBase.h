#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include <vector>

#include "../Utility/SceneName.h"
#include "../../DirectXLibrary/Graphic/Graphic.h"

class SceneBase
{
public:

	virtual ~SceneBase() {}

	/**
	 * 画面の更新を行う関数
	 */
	virtual void Update() = 0;

	/**
	 * 描画を行う関数
	 */
	virtual void Draw() = 0;

	/**
	 * Sceneの最後で呼ぶ関数
	 * @return 自分のScene名、もしくは次のScene名
	 * @detail 基本は自分のSceneNameを返し、Sceneが変わる際には次のSceneの名前が入る
	 */
	virtual SceneName Exit() = 0;

protected:
	/**
	 * 初期化関数
	 */
	virtual void Initialize() = 0;

	/**
	 * 削除関数
	 * @detail デストラクタで呼び、delete処理をメインで行う
	 */
	virtual void Delete() = 0;

	Library::Texture* texture;
	std::vector<Library::TextureData*> textureData;
};

#endif
