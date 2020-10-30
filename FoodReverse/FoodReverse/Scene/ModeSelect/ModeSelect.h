#ifndef MODE_SELECT_SCENE_H
#define MODE_SELECT_SCENE_H

#include "../../../DirectXLibrary/Device/Input/Key.h"

#include "../SceneBase.h"

class ModeSelectScene : public SceneBase
{
public:

	ModeSelectScene() { Initialize(); }
	~ModeSelectScene() { Delete(); }
	
	void Draw();

	void Update(Library::Key& key);

	SceneName Exit();

private:

	void Initialize();

	void Delete();

	int select_box_num_ = 1;

	Position pos[3] = {  Position(65,935),Position(240,270),Position(1200,270) };
	RectSize rect[3] = { RectSize(160,80),RectSize(480,540),RectSize(480,540) };
};


#endif
