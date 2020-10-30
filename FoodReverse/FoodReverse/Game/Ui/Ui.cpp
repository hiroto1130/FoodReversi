#include "Ui.h"

namespace
{
	const int FIRST_PLAYER = 0;
	const int SECOND_PLAYER = 1;
	const int NOW_PLAYER = 2;
	const int BLACK_COUNT = 3; 
	const int WHITE_COUNT = 4;
	const int NUMBER = 5;
	const int PASS = 6;
}

void Ui::Draw(bool is_pass)
{
	int texture_num = 0;

	if (now_player == Player::Player_1)
	{
		textureData[NOW_PLAYER]->position = playerUiPos_1;
		textureData[NOW_PLAYER]->uv = Uv(0, 0, 0.5, 1);
	}
	else
	{
		textureData[NOW_PLAYER]->position = playerUiPos_2;
		textureData[NOW_PLAYER]->uv = Uv(0.5, 0, 1, 1);
	}

	for (auto data : textureData)
	{
		if (texture_num == NUMBER)
		{
			DrawNumber();
		}
		else if (texture_num == PASS && is_pass == false)
		{	
		}
		else
		{
			texture->Draw(*data);
		}
		
		
		++texture_num;
	}
}

void Ui::Update()
{
	int time = motion_timer->GetMillisecondsElapsedTime();

	int Speed;
	if (motion_count < 5)
	{
		Speed = 1;
	}
	else if (motion_count >= 5)
	{
		Speed = -1;
	}
	
	if(motion_count == 10)
	{
		motion_count = 0;
	}

	if (time >= 60 )
	{
		motion_timer->TimerReset();

		if (now_player == Player::Player_1)
		{
			playerUiPos_1.y += Speed;
		}
		else
		{
			playerUiPos_2.y += Speed;
		}
		
		motion_count++;
	}

}

void Ui::Initialize()
{
	using Library::Texture;
	using Library::TextureData;

	texture = new Texture();

	motion_timer = new Timer();

	skin = &Skin::get_instance();

	TextureData* first_player = new TextureData(Position(1545, 553), RectSize(360, 140), Uv(0, 0, 0.5, 1));
	texture->Load("Texture/Ui/PlayerUi/player.png", &first_player->m_pTexture);
	textureData.push_back(first_player);

	TextureData* second_player = new TextureData(Position(46, 58), RectSize(360, 140), Uv(0.5, 0, 1, 1));
	texture->Load("Texture/Ui/PlayerUi/player.png", &second_player->m_pTexture);
	textureData.push_back(second_player);

	TextureData* now_player = new TextureData(Position(1520, 885), RectSize(360, 110), Uv(0.5, 0, 1, 1));
	texture->Load("Texture/Ui/PlayerUi/now_player.png", &now_player->m_pTexture);
	textureData.push_back(now_player);

	std::vector<Uv> uv_pos_list = skin->GetSkinTextureList();

	TextureData* black_count = new TextureData(Position(1478, 685), RectSize(500, 200), uv_pos_list[ElementName::Black_Count]);
	texture->Load("Texture/Ui/CountUi/black_count_view_ui.png", &black_count->m_pTexture);
	textureData.push_back(black_count);

	TextureData* white_count = new TextureData(Position(10, 190), RectSize(500, 200), uv_pos_list[ElementName::White_Coun]);
	texture->Load("Texture/Ui/CountUi/white_count_view_ui.png", &white_count->m_pTexture);
	textureData.push_back(white_count);

	TextureData* number_black = new TextureData(Position(0,0), RectSize(50,100), Uv(0, 0, 1, 1));
	texture->Load("Texture/Ui/Number.png", &number_black->m_pTexture);
	textureData.push_back(number_black);

	TextureData* pass = new TextureData(Position(472, 280), RectSize(980, 330), Uv(0, 0, 1, 1));
	texture->Load("Texture/Text/Pass.png", &pass->m_pTexture);
	textureData.push_back(pass);
}

void Ui::Delete()
{
	for (int texture_num = 0; texture_num < 1; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;
}

namespace
{
	const float NUMBER_TEXURE_WIDTH = 640.f;
	const float NUMBER_WIDTH = 64.f;
}

void Ui::DrawNumber()
{
	int  black_x10 = stoneConut.black_ / 10;
	int  black_x1 = stoneConut.black_ % 10;
	int  white_x10 = stoneConut.white_ / 10;
	int  white_x1 = stoneConut.white_ % 10;

	int list[4] = { white_x10, white_x1,black_x10,black_x1 };

	texture->Draw(*textureData[NUMBER]);

	Position white_pos(280, 245);
	Position black_pos(1745, 740);

	for (int count = 0; count < 4; ++count)
	{
		textureData[NUMBER]->uv.tu = (list[count] * NUMBER_WIDTH) / NUMBER_TEXURE_WIDTH;
		textureData[NUMBER]->uv.tu_size = (NUMBER_WIDTH + (NUMBER_WIDTH * list[count])) / NUMBER_TEXURE_WIDTH;
		
		if (count < 2)
		{
			white_pos.x += count * 50;
			textureData[NUMBER]->position = white_pos;
		}
		else
		{
			black_pos.x += (count % 2) * 50;
			textureData[NUMBER]->position = black_pos;
		}

		texture->Draw(*textureData[NUMBER]);
	}
}
