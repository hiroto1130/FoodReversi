#include "GameScene.h"

void GameScene::Draw()
{
	for (auto data : textureData)
	{
		texture->Draw(*data);
	}

	manager->Drow();
}

void GameScene::Update(Library::Key& key)
{
	manager->Update(key);

	if (manager->GetGameState() == true)
	{
		myScene = SceneName::ResultScene;
	}
}

SceneName GameScene::Exit()
{
	return myScene;
}

void GameScene::Initialize()
{
	skin = &Skin::get_instance();
	
	Save::create();

	std::vector<Uv> uv_pos_list = skin->GetSkinTextureList();

	Library::TextureData* texture_data = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, uv_pos_list[ElementName::Background]);
	texture->Load("Texture/BackGround/game.png",&texture_data->m_pTexture);
	textureData.push_back(texture_data);

	manager = new GameManager();
	myScene = SceneName::GameScene;
}

void GameScene::Delete()
{
	delete textureData[0];
	delete manager;
}
