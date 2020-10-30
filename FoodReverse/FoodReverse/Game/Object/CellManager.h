#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>

#include "../../../DirectXLibrary/Graphic/Graphic.h"
#include "Cell.h"
#include "../../Skin/Skin.h"

class CellManager
{
public:
	CellManager() { Initialize(); }
	~CellManager() { Delete(); }

	inline void SetState(CellState state, int cell_num)
	{
		field[cell_num]->SetState(state);
	}

	inline void SetSupport(std::vector<int>& direction, int cell_num)
	{
		field[cell_num]->SetCanInvertDirection(direction);
	}

	inline std::vector<int> GetSupprt(int cell_num) 
	{
		return field[cell_num]->GetCanInvertDirection();
	}

	inline CellState GetCellState(int cell_num)
	{
		return field[cell_num]->GetState();
	}

	inline bool CanSupport(int cell_num)
	{
		std::vector<int> invert_direction = field[cell_num]->GetCanInvertDirection();
		std::size_t size = invert_direction.size();

		if (size > 0)
		{
			return true;
		}
		return false;

	}

	inline std::vector<Cell*> GetField() { return field; }

	void Draw();

private:

	/**
	 * 初期化関数
	 */
	void Initialize();

	/**
	 * 削除関数
	 * @detail デストラクタで呼び、delete処理をメインで行う
	 */
	void Delete();

	std::vector<Cell*> field;

	Skin* skin = nullptr;
	std::vector<Uv> uv_pos_list;

	Library::Texture* texture;
	Library::TextureData* textureData;

};

#endif
