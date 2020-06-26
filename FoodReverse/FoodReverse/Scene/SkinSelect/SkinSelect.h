#ifndef SKIN_SELECT_SCENE_H
#define SKIN_SELECT_SCENE_H

#include "../SceneBase.h"

class SkinSelectScene : public SceneBase
{
public:

	SkinSelectScene() { Initialize(); }
	~SkinSelectScene() { Delete(); }

	void Draw();

	void Update();

	SceneName Exit();

private:

	void Initialize();

	void Delete();

};


#endif
