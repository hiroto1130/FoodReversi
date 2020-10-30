#include "SkinSelect.h"

namespace TextureName
{
	const int BACK_GROUND = 0;
	const int CAKE_SKIN = 1;
	const int SUSHI_SKIN = 2;
	const int NORMAL_SKIN = 3;
	const int BACK = 4;
	const int SKIN_SELECTOR = 10;
	const int SELECT_SKIN = 5;
}

namespace DataInf
{
	const int BACK = 0;
	const int NORMAL = 1;
	const int SUSHI = 2;
	const int CAKE = 3;
}

void SkinSelectScene::Draw()
{
	textureData[TextureName::SKIN_SELECTOR]->position = pos[selector_num_];
	textureData[TextureName::SKIN_SELECTOR]->texture_size = rect[selector_num_];

	for (auto data : textureData)
	{
		texture->Draw(*data);
	}
}

void SkinSelectScene::Update(Library::Key& key)
{
	if (key.IsPressed(DIK_RIGHT) == true)
	{
		if (selector_num_ == DataInf::BACK)
		{
			selector_num_ = DataInf::CAKE;
		}
		else
			if (selector_num_ == DataInf::CAKE)
			{
				selector_num_ = DataInf::SUSHI;
			}else
				if (selector_num_ == DataInf::NORMAL)
				{
					selector_num_ = DataInf::SUSHI;
				}
	}
	else
		if (key.IsPressed(DIK_LEFT) == true)
		{
			if (selector_num_ == DataInf::SUSHI)
			{
				selector_num_  = DataInf::NORMAL;
			}else
				if (selector_num_ == DataInf::NORMAL)
				{
					selector_num_ = DataInf::CAKE;
				}else
					if (selector_num_ == DataInf::CAKE)
					{
						selector_num_ = DataInf::BACK;
					}
		}
		else
			if (key.IsPressed(DIK_DOWN) == true)
			{
				if (selector_num_ == DataInf::NORMAL)
				{
					selector_num_ = DataInf::CAKE;
				}
				else
					if (selector_num_ == DataInf::SUSHI)
					{
						selector_num_ = DataInf::CAKE;
					}
					else
						if (selector_num_ == DataInf::CAKE)
						{
							selector_num_ = DataInf::BACK;
						}
			}
			else
				if (key.IsPressed(DIK_UP) == true)
				{
					if (selector_num_ == DataInf::BACK)
					{
						selector_num_ = DataInf::CAKE;
					}else
						if (selector_num_ == DataInf::CAKE)
					{
						selector_num_ = DataInf::NORMAL;
					}
				}

	if (key.IsPressed(DIK_RETURN) == true)
	{
		switch (selector_num_)
		{
		case DataInf::BACK:
			myScene = SceneName::TitleScene;
			break;
		case DataInf::NORMAL:
			texture->Load("Texture/Icon/normal.png", &textureData[TextureName::SELECT_SKIN]->m_pTexture);
			skin->SetSkin(SkinName::Normal);
			break;
		case DataInf::SUSHI:
			texture->Load("Texture/Icon/sushi.png", &textureData[TextureName::SELECT_SKIN]->m_pTexture);
			skin->SetSkin(SkinName::Sushi);
			break;
		case DataInf::CAKE:
			texture->Load("Texture/Icon/cake.png", &textureData[TextureName::SELECT_SKIN]->m_pTexture);
			skin->SetSkin(SkinName::Cake);
		default:
			break;
		}
	}
}

SceneName SkinSelectScene::Exit()
{
    return myScene;
}

void SkinSelectScene::Initialize()
{
	texture = new Library::Texture();

	skin = &Skin::get_instance();

	motion_timer = new Timer();

	Library::TextureData* back_ground = new Library::TextureData(Position{ 0,0 }, RectSize{ 1920,1080 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/BackGround/skin.png", &back_ground->m_pTexture);
	textureData.push_back(back_ground);

	Library::TextureData* cake_skin = new Library::TextureData(Position{ 576,560 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Icon/cake.png", &cake_skin->m_pTexture);
	textureData.push_back(cake_skin);

	Library::TextureData* sushi_skin = new Library::TextureData(Position{ 989,154 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Icon/sushi.png", &sushi_skin->m_pTexture);
	textureData.push_back(sushi_skin);

	Library::TextureData* normal_skin = new Library::TextureData(Position{ 576,154 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Icon/normal.png", &normal_skin->m_pTexture);
	textureData.push_back(normal_skin);

	Library::TextureData* back = new Library::TextureData(Position{ 51,944 }, RectSize{ 200,100 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Text/back.png", &back->m_pTexture);
	textureData.push_back(back);

	Library::TextureData* select_skin = new Library::TextureData(Position{ 64,16 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Icon/normal.png", &select_skin->m_pTexture);
	textureData.push_back(select_skin);

	Library::TextureData* selecter_skin = new Library::TextureData(Position{ 53,5 }, RectSize{ 390,390 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/Select_B.png", &selecter_skin->m_pTexture);
	textureData.push_back(selecter_skin);

	Library::TextureData* selecter_skin_normal = new Library::TextureData(Position{ 576,560 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/Select_G.png", &selecter_skin_normal->m_pTexture);
	textureData.push_back(selecter_skin_normal);
	Library::TextureData* selecter_skin_sushi = new Library::TextureData(Position{ 576,154 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/Select_G.png", &selecter_skin_sushi->m_pTexture);
	textureData.push_back(selecter_skin_sushi);
	Library::TextureData* selecter_skin_cake = new Library::TextureData(Position{ 989, 154 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/Select_G.png", &selecter_skin_cake->m_pTexture);
	textureData.push_back(selecter_skin_cake);

	Library::TextureData* skin_selector = new Library::TextureData(Position{ 576,560 }, RectSize{ 366,366 }, Uv{ 0,0,1,1 });
	texture->Load("Texture/Selector/skin.png", &skin_selector->m_pTexture);
	textureData.push_back(skin_selector);

	myScene = SceneName::SkinSelectScene;
}

void SkinSelectScene::Delete()
{
	for (int texture_num = 0; texture_num < 1; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;

}
