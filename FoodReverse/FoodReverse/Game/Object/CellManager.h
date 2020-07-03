#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>

#include "../../../DirectXLibrary/Graphic/Graphic.h"
#include "Cell.h"

class CellManager
{
public:
	CellManager() { Initialize(); }
	~CellManager() { Delete(); }

	inline void ColorChange(CellState state, int cell_pos)
	{
		field[cell_pos]->SetState(state);
	}

	inline void SetSupport(std::vector<Direction> direction, int cell_pos)
	{
		field[cell_pos]->SetCanInvertDirection(direction);
	}

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

	Library::Texture* texture;
	std::vector<Library::TextureData*> textureData;

};

#endif
