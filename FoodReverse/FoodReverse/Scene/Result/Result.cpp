#include "Result.h"

namespace
{
	const int BACK_GROUND = 0;
	const int BACK_TITLE_TEXT = 1;
	const int ONCE_MORE_TEXT = 2;
	const int SELECTER = 3;
	const int WINNER_TEXT = 4;
}

void ResultScene::Draw()
{
	texture->Draw(*textureData[BACK_GROUND]);
	texture->Draw(*textureData[BACK_TITLE_TEXT]);
	texture->Draw(*textureData[ONCE_MORE_TEXT]);
	texture->Draw(*textureData[SELECTER]);

	for (auto data: field)
	{
		texture->Draw(*data);
	}

	texture->Draw(*textureData[WINNER_TEXT]);
}

void ResultScene::Update(Library::Key& key)
{
	if (key.IsPressed(DIK_LEFT))
	{
		textureData[SELECTER]->position = Position(50, 885);
	}
	else if (key.IsPressed(DIK_RIGHT))
	{
		textureData[SELECTER]->position = Position(1520, 885);
	}

	if (key.IsPressed(DIK_RETURN))
	{
		if (textureData[SELECTER]->position.x == 50)
		{
			myScene = SceneName::TitleScene;
		}
		else
		{
			myScene = SceneName::GameScene;
		}
	}
}

SceneName ResultScene::Exit()
{
	return myScene;
}

void ResultScene::Initialize()
{
	skin = &Skin::get_instance();
	std::vector<Uv> uv_pos_list = skin->GetSkinTextureList();

	save = &Save::get_instance();
	last_field_state = save->GetLastField();
	winner_ = save->GetWinner();

	myScene = SceneName::ResultScene;

	using Library::TextureData;

	Library::TextureData* texture_data = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, uv_pos_list[ElementName::Background]);
	texture->Load("Texture/BackGround/game.png", &texture_data->m_pTexture);
	textureData.push_back(texture_data);

	TextureData* bcek_title = new TextureData(Position(50, 885), RectSize(300, 150), Uv(0, 0, 1, 1));
	texture->Load("Texture/Text/BackTitle.png", &bcek_title->m_pTexture);
	textureData.push_back(bcek_title);

	TextureData* once_more = new TextureData(Position(1520, 885), RectSize(300, 150), Uv(0, 0, 1, 1));
	texture->Load("Texture/Text/OnceMore.png", &once_more->m_pTexture);
	textureData.push_back(once_more);

	TextureData* selector = new TextureData(Position(50, 885), RectSize(300, 150), Uv(0, 0, 1, 1));
	texture->Load("Texture/Selector/game.png", &selector->m_pTexture);
	textureData.push_back(selector);

	ReconstructionField();

	SetWinnerTextureData();
}

namespace
{
	const int MAX_CELL = 64;
	const int WHITE = 0;
	const int BLACK = 1;
	const int CELL_START_POS_WIDTH = 512;
	const int CELL_START_POS_HEIGHT = 92;
	const int CELL_SIZE = 112;
}

void ResultScene::ReconstructionField()
{
	std::vector<Uv> uv_pos_list = skin->GetSkinTextureList();

	LPDIRECT3DTEXTURE9 pTexture;
	texture->Load("Texture/Motion/invert.png", &pTexture);

	float tv = uv_pos_list[ElementName::Motion].tv;
	float tv_size = uv_pos_list[ElementName::Motion].tv_size;

	Position pos(0, 0);
	for (int create_cell = 0; create_cell < MAX_CELL; ++create_cell)
	{
		pos.x = CELL_START_POS_WIDTH + (CELL_SIZE * (create_cell % 8));
		pos.y = CELL_START_POS_HEIGHT + (CELL_SIZE * (create_cell / 8));

		field.push_back(nullptr);
		field[create_cell] = new Library::TextureData(pos, RectSize(112, 112), Uv(0, 0, 0, 0), pTexture);

		if (last_field_state[create_cell] == CellState::ExistWhiteStone)
		{
			field[create_cell]->uv = Uv(448.f / 896.f, tv, 560.f / 896.f, tv_size);
		}
		else if (last_field_state[create_cell] == CellState::ExistBlackStone)
		{
			field[create_cell]->uv = Uv(0, tv, 112.f / 896.f, tv_size);
		}
	}
}

void ResultScene::SetWinnerTextureData()
{
	using Library::TextureData;

	TextureData* winner;
	if(winner_ == Player::Player_1)
	{
		winner = new TextureData(Position(300, 150), RectSize(1278, 310), Uv(0, 0, 1, 1));
		texture->Load("Texture/Text/FirstPlayerWin.png", &winner->m_pTexture);
		textureData.push_back(winner);
	}
	else if (winner_ == Player::Player_2)
	{
		winner = new TextureData(Position(300, 150), RectSize(1278, 310), Uv(0, 0, 1, 1));
		texture->Load("Texture/Text/SecondPlayerWin.png", &winner->m_pTexture);
		textureData.push_back(winner);
	}
}

void ResultScene::Delete()
{
	if (myScene == SceneName::TitleScene)
	{
		Skin::destroy();
		Save::destroy();
	}

	delete texture;

	for (auto data : textureData)
	{
		delete data;
	}

	for (auto data : field)
	{
		delete data;
	}
}
