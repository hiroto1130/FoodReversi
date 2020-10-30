#ifndef CELL_H
#define CELL_H

#include <vector>

#include "../../Utility/CellState.h"
#include "../../Utility/Direction.h"
#include "../../Skin/Skin.h"

class Cell
{
public:
	Cell(Position pos, LPDIRECT3DTEXTURE9 pTexture)
	{
		texture_data = new Library::TextureData(pos,RectSize(112,112),Uv(0,0,0,0),pTexture);
		skin = &Skin::get_instance();
		uv_pos_list = skin->GetSkinTextureList();
	}
	~Cell() { delete texture_data; }

	CellState GetState() { return state; };

	void SetState(CellState chang_state) 
	{
		state = chang_state; 
		float tv = uv_pos_list[ElementName::Motion].tv;
		float tv_size = uv_pos_list[ElementName::Motion].tv_size;
		switch (chang_state)
		{
		case CellState::ExistBlackStone:
			texture_data->uv = Uv(0, tv, 112.f / 896.f, tv_size);
			break;
		case CellState::ExistWhiteStone:
			texture_data->uv = Uv(448.f / 896.f, tv, 560.f / 896.f,tv_size);
			break;
		default:
			break;
		}
	};

	std::vector<int> GetCanInvertDirection() { return can_invert_direction; }

	void SetCanInvertDirection(std::vector<int>& direction)
	{
		can_invert_direction.clear();
		can_invert_direction = direction; 
	}

	void SetUv(Uv uv)
	{
		texture_data->uv = uv;
	}

	Library::TextureData GetTextureData()
	{
		return *texture_data;
	}

private:

	Library::TextureData* texture_data;

	CellState state = CellState::Invisible;

	std::vector<int> can_invert_direction;

	Skin* skin = nullptr;
	std::vector<Uv> uv_pos_list;
};

#endif
