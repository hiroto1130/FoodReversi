#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "../../../DirectXLibrary/Device/Input/Key.h"

#include "../SceneBase.h"
#include "../../Skin/Skin.h"
#include "../../Game/Object/CellManager.h"
#include "../../Utility/Player.h"
#include "../../Save/Save.h"

class ResultScene : public SceneBase
{
public:

	ResultScene() { Initialize(); }
	~ResultScene() { Delete(); }

	void Draw();

	void Update(Library::Key& key);

	SceneName Exit();

private:

	void Initialize();

	void Delete();

	void ReconstructionField();

	void SetWinnerTextureData();

	Skin* skin = nullptr;

	Save* save = nullptr;
	std::vector<CellState> last_field_state;
	Player winner_;

	std::vector<Library::TextureData*> field;
};


#endif
