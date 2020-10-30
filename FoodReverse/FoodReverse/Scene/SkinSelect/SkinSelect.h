#ifndef SKIN_SELECT_SCENE_H
#define SKIN_SELECT_SCENE_H

#include "../../../DirectXLibrary/Device/Input/Key.h"

#include "../SceneBase.h"
#include "../../Skin/Skin.h"
#include "../../Utility/Timer/Timer.h"

class SkinSelectScene : public SceneBase
{
public:

	SkinSelectScene() { Initialize(); }
	~SkinSelectScene() { Delete(); }

	void Draw();

	void Update(Library::Key& key);

	SceneName Exit();

private:

	void Initialize();

	void Delete();

	int selector_num_ = 3;

	Position pos[4] = { Position(51,944),Position(576,154),Position(989,154),Position(576,560) };
	RectSize rect[4] = { RectSize(200,100), RectSize(366,366),RectSize(366,366),RectSize(366,366) };

	SkinName now_skin = SkinName::Normal;

	Skin* skin = nullptr;

	Timer* motion_timer;
};

#endif
