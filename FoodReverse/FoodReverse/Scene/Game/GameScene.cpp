#include "GameScene.h"

void GameScene::Draw()
{
	for (auto data : textureData)
	{
		texture->Draw(*data);
	}
}

void GameScene::Update()
{
}

SceneName GameScene::Exit()
{
	return SceneName::GameScene;
}

void GameScene::Initialize()
{
	Library::TextureData* texture_data = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/game_background.png",&texture_data->m_pTexture);
	textureData.push_back(texture_data);
}

void GameScene::Delete()
{
	delete textureData[0];
}
