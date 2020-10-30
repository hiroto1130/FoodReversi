#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "../../../DirectXLibrary/Device/Input/Key.h"

#include "../SceneBase.h"

class TitleScene : public SceneBase
{
public:

	TitleScene() { Initialize(); }
	~TitleScene() { Delete(); }

	void Draw();

	void Update(Library::Key& key);

	SceneName Exit();

private:

	void Initialize();

	void Delete();
	
	bool can_darw_select_skin = false;

	bool can_draw_select_game = true;

};

#endif
