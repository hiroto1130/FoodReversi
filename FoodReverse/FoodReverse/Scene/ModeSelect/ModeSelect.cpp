#include "ModeSelect.h"

namespace
{
	const int BACK_GROUND = 0;
	const int SELECTOR = 1;
}

void ModeSelectScene::Draw()
{
	textureData[SELECTOR]->position = pos[select_box_num_];
	textureData[SELECTOR]->texture_size = rect[select_box_num_];

	for (auto data : textureData)
	{
		texture->Draw(*data);
	}
}

void ModeSelectScene::Update(Library::Key& key)
{
	if (key.IsPressed(DIK_RIGHT) == true)
	{
		if (select_box_num_ < 2)
		{
			select_box_num_ += 1;
		}
	}else
	if (key.IsPressed(DIK_LEFT) == true)
	{
		if (select_box_num_ > 0)
		{
			select_box_num_ -= 1;
		}
	}else
	if (key.IsPressed(DIK_DOWN) == true)
	{
		select_box_num_ = 0;
	}else
	if (key.IsPressed(DIK_UP) == true)
	{
		if (select_box_num_ == 0)
		{
			select_box_num_ = 1;
		}
	}

	if (key.IsPressed(DIK_RETURN) == true)
	{
		switch (select_box_num_)
		{
		case 0:
			myScene = SceneName::TitleScene;
			break;
		case 1:
			myScene = SceneName::GameScene;
			break;
		case 2:
			myScene = SceneName::SkinSelectScene;
			break;
		default:
			break;
		}
	}
}

SceneName ModeSelectScene::Exit()
{
	return myScene;
}

void ModeSelectScene::Initialize()
{
	texture = new Library::Texture();

	Library::TextureData* back_ground = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/BackGround/mode.png", &back_ground->m_pTexture);
	textureData.push_back(back_ground);

	Library::TextureData* selector = new Library::TextureData(Position{ 240,270 }, RectSize{ 480,540 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/game.png", &selector->m_pTexture);
	textureData.push_back(selector);

	myScene = SceneName::ModeSelectScene; 
}

void ModeSelectScene::Delete()
{
	for (int texture_num = 0; texture_num < 1; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;
}