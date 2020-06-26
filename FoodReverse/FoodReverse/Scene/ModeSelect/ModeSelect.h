#ifndef MODE_SELECT_SCENE_H
#define MODE_SELECT_SCENE_H

#include "../SceneBase.h"

class ModeSelectScene : public SceneBase
{
public:

	ModeSelectScene() { Initialize(); }
	~ModeSelectScene() { Delete(); }
	
	void Draw();

	void Update();

	SceneName Exit();

private:

	void Initialize();

	void Delete();
};


#endif
