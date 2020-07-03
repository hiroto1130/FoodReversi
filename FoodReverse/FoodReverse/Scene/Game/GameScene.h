#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "../../../DirectXLibrary/Graphic/Graphic.h"

#include "../SceneBase.h"
#include "../../Game/GameManager/GameManager.h"

class GameScene : public SceneBase
{
public:

	GameScene() { Initialize(); }
	~GameScene() { Delete(); }

	void Draw();

	void Update();

	SceneName Exit();

private:

	void Initialize();

	void Delete();

	GameManager* manager = nullptr;
};


#endif
