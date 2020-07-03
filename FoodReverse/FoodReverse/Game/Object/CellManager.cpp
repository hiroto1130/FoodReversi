#include  "CellManager.h"

namespace 
{
	const int MAX_CELL = 64;
	const int WHITE = 0;
	const int BLACK = 1;
}

void CellManager::Draw()
{

	for (auto cell_num : field)
	{
		if (cell_num->GetState() == CellState::ExistBlackStone)
		{
			texture->Draw(*textureData[WHITE]);
		}
		else if (cell_num->GetState() == CellState::ExistWhiteStone)
		{
			texture->Draw(*textureData[BLACK]);
		}
	}

}

void CellManager::Initialize()
{
	using Library::Texture;
	using Library::TextureData;

	for (int create_cell = 0; create_cell < MAX_CELL; ++create_cell)
	{
		field.push_back(nullptr);
		field[create_cell] = new Cell();
	}

	texture = new Texture();

	TextureData* white = new TextureData(Position(0, 0), RectSize(108, 108), Uv(0, 0, 1, 1));
	texture->Load("white", &white->m_pTexture);
	textureData.push_back(white);

	TextureData* black = new TextureData(Position(0,0),RectSize(108,108),Uv(0,0,1,1));
	texture->Load("black", &black->m_pTexture);
	textureData.push_back(black);
	
}

void CellManager::Delete()
{
	for (int delete_cell = 0; delete_cell < MAX_CELL; ++delete_cell)
	{
		delete field[delete_cell];
	}

	for (int texture_num = 0; texture_num < 2; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;
}
