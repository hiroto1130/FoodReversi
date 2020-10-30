#include  "CellManager.h"

namespace 
{
	const int MAX_CELL = 64;
	const int WHITE = 0;
	const int BLACK = 1;
	const int CELL_START_POS_WIDTH = 512;
	const int CELL_START_POS_HEIGHT = 92;
	const int CELL_SIZE = 112;
}

void CellManager::Draw()
{
	for (int draw_cell = 0; draw_cell < MAX_CELL; ++draw_cell)
	{
		textureData = &field[draw_cell]->GetTextureData();

		texture->Draw(*textureData);
	}
}

void CellManager::Initialize()
{
	using Library::Texture;
	using Library::TextureData;

	texture = new Texture();

	skin = &Skin::get_instance();
	uv_pos_list = skin->GetSkinTextureList();

	LPDIRECT3DTEXTURE9 pTexture;
	texture->Load("Texture/Motion/invert.png", &pTexture);

	Position pos(0, 0);
	float tv = uv_pos_list[ElementName::Motion].tv;
	float tv_size = uv_pos_list[ElementName::Motion].tv_size;

	for (int create_cell = 0; create_cell < MAX_CELL; ++create_cell)
	{
		pos.x = CELL_START_POS_WIDTH + (CELL_SIZE * (create_cell % 8));
		pos.y = CELL_START_POS_HEIGHT + (CELL_SIZE * (create_cell / 8));

		field.push_back(nullptr);
		field[create_cell] = new Cell(pos,pTexture);

		if (create_cell == 28 || create_cell == 35)
		{
			field[create_cell]->SetState(CellState::ExistWhiteStone);
			field[create_cell]->SetUv(Uv(448.f / 896.f,tv, 560.f / 896.f,tv_size));
		}
		else if (create_cell == 27 || create_cell == 36)
		{
			field[create_cell]->SetState(CellState::ExistBlackStone);
			field[create_cell]->SetUv(Uv(0, tv, 112.f / 896.f, tv_size));
		}
		else
		{
			field[create_cell]->SetState(CellState::Invisible);
		}
	}
}

void CellManager::Delete()
{
	for (int delete_cell = 0; delete_cell < MAX_CELL; ++delete_cell)
	{
		delete field[delete_cell];
	}

	delete texture;
}
