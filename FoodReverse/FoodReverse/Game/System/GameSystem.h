#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include <vector>

#include "../Object/CellManager.h"
#include "../../../DirectXLibrary/Device/Input/Key.h"
#include "../../Utility/Player.h"
#include "../Ui/Ui.h"
#include "../../Utility/StoneCount.h"
#include "../../Utility/Timer/Timer.h"
#include "../../Skin/Skin.h"

class GameSystem
{
public:
	GameSystem(CellManager& manager) { Initialize(manager); }
	~GameSystem() { Delete(); }

	void Draw(CellManager& manager);

	void Update(Library::Key& key,CellManager& manager, Ui& ui,bool& is_pass);

	StoneCount StoneCounter(CellManager& manager);

	bool IsEndGame(CellManager& manager);

	inline std::vector<int> GetInvertCellNum()
	{
		return invert_cell_num;
	}

private:

	/**
	 * 初期化関数
	 */
	void Initialize(CellManager& manager);

	/**
	 * 削除関数
	 * @detail デストラクタで呼び、delete処理をメインで行う
	 */
	void Delete();

	void SetStone(Library::Key& key,CellManager& manager,Ui& ui);

	void Invert(CellManager& manager, int cell_num);

	int Search(int list_num, int cell_num, CellState check_color, std::vector<Cell*> field, int repeat_count);

	void Support(CellManager& manager);

	bool CanSeeDirection(int cell_num, int repeat_count);

	void DrawSelector(int move_val);

	void DrawSupporter(CellManager& manager);

	int Input(Library::Key& key);

	void PassCheck(CellManager& manager);
	bool is_player_pass = false;

	void PlayerChange(CellManager& manager, Ui& ui);

	const int first_select_cell_ = 26;

	int move_val_ = 0;

	int now_pos = 26;

	int support_motion_count_ = 1;

	Player now_player_ = Player::Player_1;

	int check_list_[8][2] =
	{
		{ 0,-8},
		{ 0, 8},
		{ 1, 0},
		{-1, 0},
		{ 1,-8},
		{-1,-8},
		{ 1, 8},
		{-1, 8}
	};

	Skin* skin = nullptr;
	std::vector<Uv> uv_pos_list;

	std::vector<int> invert_cell_num;

	Timer* timer = nullptr;
	
	Timer* pass_timer = nullptr;

	Timer* invert_motion_timer = nullptr;
	void InvertMotion(CellManager& manager);
	int motion_count = 0;

	Library::Texture* texture = nullptr;
	std::vector<Library::TextureData*> textureData;

};

#endif
