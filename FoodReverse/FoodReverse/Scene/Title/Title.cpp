#include "Title.h"

namespace TextrueData
{
	const int back_ground = 0;
	const int select_game = 1;
	const int select_skin = 2;
}

void TitleScene::Draw()
{
	texture->Draw(*textureData[0]);

	if (can_draw_select_game == true)
	{
		texture->Draw(*textureData[1]);
	}
	else if (can_darw_select_skin == true)
	{
		texture->Draw(*textureData[2]);
	}
}

void TitleScene::Update(Library::Key& key)
{
	if (key.IsPressed(DIK_RIGHT))
	{
		can_darw_select_skin = false;
		can_draw_select_game = true;
	}
	else if (key.IsPressed(DIK_LEFT))
	{
		can_darw_select_skin = true;
		can_draw_select_game = false;
	}

	if (key.IsPressed(DIK_RETURN))
	{
		if (can_draw_select_game == true)
		{
			myScene = SceneName::GameScene;
		}
		else if (can_darw_select_skin == true)
		{
			myScene = SceneName::SkinSelectScene;
		}
	}
}

SceneName TitleScene::Exit()
{
	return myScene;
}

void TitleScene::Initialize()
{
	texture = new Library::Texture();

	Library::TextureData* texture_data = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/BackGround/title.png", &texture_data->m_pTexture);
	textureData.push_back(texture_data);

	Library::TextureData* select_game = new Library::TextureData(Position{435,718}, RectSize{1065,227}, Uv{ 0,0,1,1 });
	texture->Load("Texture/button/select_game.png", &select_game->m_pTexture);
	textureData.push_back(select_game);

	Library::TextureData* select_skin = new Library::TextureData(Position{ 52,804 }, RectSize{ 259,254 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/button/select_skin.png", &select_skin->m_pTexture);
	textureData.push_back(select_skin);

	myScene = SceneName::TitleScene;
}

void TitleScene::Delete()
{
	for (int texture_num = 0; texture_num < 3; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;
}
