#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "../SceneBase.h"

class TitleScene : public SceneBase
{
public:

	TitleScene() { Initialize(); }
	~TitleScene() { Delete(); }

	void Draw();

	void Update();

	SceneName Exit();

private:

	void Initialize();

	void Delete();

};

#endif
