#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "../SceneBase.h"

class ResultScene : public SceneBase
{
public:

	ResultScene() { Initialize(); }
	~ResultScene() { Delete(); }

	void Draw();

	void Update();

	SceneName Exit();

private:

	void Initialize();

	void Delete();

};


#endif
