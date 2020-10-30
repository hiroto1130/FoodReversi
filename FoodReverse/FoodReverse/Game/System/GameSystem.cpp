#include "GameSystem.h"

namespace
{
	const int UP         = 0;
	const int DOWN       = 1;
	const int RIGHT      = 2;
	const int LEFT       = 3;
	const int UP_RIGHT   = 4;
	const int UP_LEFT    = 5;
	const int DOWN_RIGHT = 6;
	const int DOWN_LEFT  = 7;
	const int ADD_X      = 0;
	const int ADD_Y      = 1;

	const int MAX_CELL   = 63;
	const int MIN_CELL   = 0;
}

// ここで裏返す部分のセルの場所が来る(何も置かれていない状態確定)
void GameSystem::Invert(CellManager& manager, int cell_num)
{
	std::vector<int> invert_direction = manager.GetSupprt(cell_num);

	int x = 0, y = 0,next_cell = 0, repeat_count = 0;

	CellState invert_color;
	
	if (now_player_ == Player::Player_1)
	{
		invert_color = CellState::ExistBlackStone;
		manager.SetState(invert_color, cell_num);
	}
	else
	{
		invert_color = CellState::ExistWhiteStone;
		manager.SetState(invert_color, cell_num);
	}

	for (auto direction : invert_direction)
	{
		x = check_list_[direction][ADD_X];
		y = check_list_[direction][ADD_Y];

		while (true)
		{
			++repeat_count;
			next_cell = (x * repeat_count) + (y * repeat_count) + cell_num;

			if (manager.GetCellState(next_cell) == invert_color)
			{
				break;
			}

			manager.SetState(invert_color, next_cell);
			invert_cell_num.push_back(next_cell);
		}

		repeat_count = 0;
	}
}

int GameSystem::Search(int direction_num, int cell_num, CellState check_color, std::vector<Cell*> field, int repeat_count)
{
	int x = check_list_[direction_num][ADD_X];
	int y = check_list_[direction_num][ADD_Y];

	//  位置計算      X座標の移動量         Y座標の移動量   現在の位置
	int next_cell = (x * repeat_count) + (y * repeat_count) + cell_num;

	if (direction_num == RIGHT || direction_num == UP_RIGHT || direction_num == DOWN_RIGHT)
	{
		if (next_cell % 8 == 0)
		{
			return false;
		}
	}
	else if (direction_num == LEFT || direction_num == UP_LEFT || direction_num == DOWN_LEFT)
	{
		if (next_cell % 8 == 7)
		{
			return false;
		}
	}

	// 次の方向のCellを確認しても良いか
	if (CanSeeDirection(next_cell, direction_num) == false)
	{
		return false;
	}

	CellState state = field[next_cell]->GetState();

	// 次のマスに何もなかった場合
	if (state == CellState::Invisible)
	{
		return false;
	}else // 次のマスに自分と同じ色の石があった場合
		if (state == check_color && repeat_count == 1)
		{
			return false;
		}
	
	//	次のマスがひっくり返せる対象だった場合 (無い場合は前のif文ではじく)
	if (state != check_color)
	{
		++repeat_count;
		if (Search(direction_num, cell_num, check_color, field, repeat_count) == true)
		{
			return true;
		}

		else { return false; }

	}

	if (state == check_color)
	{
		return true;
	}

}

/*ここで取得するCellの番号は次確認するCellの番号*/
bool GameSystem::CanSeeDirection(int cell_num,int repeat_count)
{
	// 配列外を見ないための処理
	if (cell_num < MIN_CELL || cell_num > MAX_CELL)
	{
		return false;
	}

	// 右端から自分より一段下の左端を見ないための処理
	if (repeat_count == RIGHT && cell_num % 8 == 0)
	{
		return false;
	}

	// 左端から自分より一段上の右端を見ないための処理
	if (repeat_count == LEFT && cell_num % 8 == 7)
	{
		return false;
	}

	return true;
}

void GameSystem::Support(CellManager& manager)
{
	std::vector<Cell*> filed = manager.GetField();

	std::vector<int> invert_direction;
	
	CellState check_color;

	if (now_player_ == Player::Player_1)
	{
		check_color = CellState::ExistBlackStone;
	}
	else
	{
		check_color = CellState::ExistWhiteStone;
	}

	// MaxCell(64)分回す
	for (int current_cell = 0; current_cell < MAX_CELL + 1; ++current_cell)
	{
		// 何も置かれていなセルのみ見る
		if (manager.GetCellState(current_cell) == CellState::Invisible)
		{
			// 全8方向を見る
			for (int direction_num = 0; direction_num < 8; ++direction_num)
			{
				bool result = Search(direction_num, current_cell, check_color, filed, 1);/*最後の引数は[ 1 ]で固定値(回帰処理の為)*/
				if (result == true)
				{
					invert_direction.push_back(direction_num);
				}
			}
		}
		manager.SetSupport(invert_direction, current_cell);

		invert_direction.clear();
	}
}

namespace
{
	const int CELL_START_POS_WIDTH  = 512;
	const int CELL_START_POS_HEIGHT = 92;
	const int CELL_SIZE             = 112;
}

namespace TextureList
{
	const int SELECTOR = 0;
	const int SUPPORT  = 1;
}

void GameSystem::Draw(CellManager& manager)
{
	DrawSelector(move_val_);
	DrawSupporter(manager);
}

void GameSystem::Update(Library::Key& key, CellManager& manager, Ui& ui,bool& is_pass)
{
	PassCheck(manager);

	if (is_player_pass == false)
	{
		move_val_ = Input(key);
		SetStone(key, manager, ui);
		pass_timer->TimerReset();
	}
	else
	{
		if (pass_timer->GetSecondsElapsedTime() >= 2)
		{
			PlayerChange(manager, ui);
		}
	}

	InvertMotion(manager);

	is_pass = is_player_pass;
}


StoneCount GameSystem::StoneCounter(CellManager& manager)
{
	StoneCount count;

	for (int check_cell_num = 0; check_cell_num < MAX_CELL + 1; ++check_cell_num)
	{
		if (manager.GetCellState(check_cell_num) == CellState::ExistBlackStone)
		{
			++count.black_;
		}
		else if (manager.GetCellState(check_cell_num) == CellState::ExistWhiteStone)
		{
			++count.white_;
		}

	}

	return count;
}

bool GameSystem::IsEndGame(CellManager& manager)
{
	StoneCount count;

	count = StoneCounter(manager);

	if (count.black_ == 0 || count.white_ == 0)
	{
		return true;
	}

	for (int check_cell_num = 0; check_cell_num < MAX_CELL + 1; ++check_cell_num)
	{
		if (manager.GetCellState(check_cell_num) == CellState::Invisible)
		{
			return false;
		}
	}


	return true;
}

int GameSystem::Input(Library::Key& key)
{
	int move_val = 0;

	if (key.IsPressed(DIK_UP))
	{
		move_val += -8;
	}else
	if (key.IsPressed(DIK_DOWN))
	{
		move_val += 8;
	}else
	if (key.IsPressed(DIK_RIGHT))
	{
		move_val += 1;
	}else
	if (key.IsPressed(DIK_LEFT))
	{
		move_val += -1;
	}

	return move_val;
}

void GameSystem::PassCheck(CellManager& manager)
{
	std::vector<Cell*> filed = manager.GetField();

	for (int cell_num = 0; cell_num < MAX_CELL; ++cell_num)
	{
		std::vector<int> invert_direction =  filed[cell_num]->GetCanInvertDirection();

		if (invert_direction.size() > 0)
		{
			 is_player_pass = false;
			 return;
		}

	}

	is_player_pass = true;
	return;

}

void GameSystem::PlayerChange(CellManager& manager, Ui& ui)
{
	if (now_player_ == Player::Player_1)
	{
		now_player_ = Player::Player_2;
	}
	else
	{
		now_player_ = Player::Player_1;
	}

	now_pos = 36;
	Support(manager);
	ui.SetNowPlayer(now_player_);
}

void GameSystem::InvertMotion(CellManager& manager)
{
	int time = invert_motion_timer->GetMillisecondsElapsedTime();
	
	if (invert_cell_num.size() == 0)
	{
		return;
	}

	
	if (time < 50)
	{
		return;
	}
	else
	{
		++motion_count;
	}

	invert_motion_timer->TimerReset();
	
	float tu = 0, tu_size = 0;
	float tv = uv_pos_list[ElementName::Motion].tv;
	float tv_size = uv_pos_list[ElementName::Motion].tv_size;
	std::vector<Cell*> filed = manager.GetField();

	for (auto cell_num : invert_cell_num)
	{
		switch (filed[cell_num]->GetState())
		{
		case CellState::ExistWhiteStone:
			tu =  112.f * motion_count / 896.f;
			tu_size = ((112.f * motion_count) + 112.f)/ 896.f;
			break;
		case CellState::ExistBlackStone:
			if (motion_count == 4)
			{
				tu = 0;
				tu_size = 112.f / 896.f;
			}
			else
			{
				tu = ((112.f * motion_count) + 448.f) / 896.f;
				tu_size = ((112.f * motion_count) + 560.f) / 896.f;
			}
			break;
		}

		filed[cell_num]->SetUv(Uv(tu,tv,tu_size,tv_size));
	}

	if (motion_count == 4)
	{
		invert_cell_num.clear();
		motion_count = 0;
	}
}

void GameSystem::DrawSelector(int move_val)
{
	Position pos(0, 0);

	int previously_val = now_pos;
	now_pos += move_val;
	if (previously_val % 8 == 0 && move_val == -1)
	{
		now_pos += 8;
	}
	else if (previously_val % 8 == 7 && move_val == 1)
	{
		now_pos -= 8;
	} 
	else if (previously_val / 8 == 0 && move_val == -8)
	{
		now_pos += 64;
	}
	else if (previously_val / 8 == 7 && move_val == 8)
	{
		now_pos -= 64;
	}

	pos.x = CELL_START_POS_WIDTH + (CELL_SIZE * (now_pos % 8));
	pos.y = CELL_START_POS_HEIGHT + (CELL_SIZE * (now_pos / 8));

	textureData[TextureList::SELECTOR]->position = pos;

	texture->Draw(*textureData[TextureList::SELECTOR]);
}

void GameSystem::DrawSupporter(CellManager& manager)
{
	Position pos{0,0};

	// motion
	if (timer->GetMillisecondsElapsedTime() > 90 )
	{
		timer->TimerReset();
		textureData[TextureList::SUPPORT]->uv.tu = (support_motion_count_ * 112.f) / 1120.f;
		++support_motion_count_;
		textureData[TextureList::SUPPORT]->uv.tu_size = (support_motion_count_ * 112.f) / 1120.f;

		if (support_motion_count_ == 10)
		{
			support_motion_count_ = 0;
		}
	}

	for (int cell_val = 0; cell_val < MAX_CELL +1; ++cell_val)
	{
		if (manager.CanSupport(cell_val) == true)
		{
			pos.x = CELL_START_POS_WIDTH + (CELL_SIZE * (cell_val % 8));
			pos.y = CELL_START_POS_HEIGHT + (CELL_SIZE * (cell_val / 8));

			textureData[TextureList::SUPPORT]->position = pos;
			texture->Draw(*textureData[TextureList::SUPPORT]);
		}

	}
}

void GameSystem::Initialize(CellManager& manager)
{
	using Library::Texture;
	using Library::TextureData;

	timer = new Timer();
	invert_motion_timer = new Timer();
	pass_timer = new Timer();

	texture = new Texture();

	TextureData* selector = new TextureData(Position(0, 0), RectSize(112, 112), Uv(0, 0, 1, 1));
	texture->Load("Texture/Selector/game.png", &selector->m_pTexture);
	textureData.push_back(selector);

	TextureData* support = new TextureData(Position(0, 0), RectSize(112, 112), Uv(0, 0,  112.f / 560.f, 1));
	texture->Load("Texture/Motion/support.png", &support->m_pTexture);
	textureData.push_back(support);

	Support(manager);

	skin = &Skin::get_instance();
	uv_pos_list = skin->GetSkinTextureList();
}

void GameSystem::Delete()
{
	for (int texture_num = 0; texture_num < 1; ++texture_num)
	{
		delete textureData[texture_num];
	}

	delete texture;

	delete timer;
}

void GameSystem::SetStone(Library::Key& key,CellManager& manager,Ui& ui)
{
	if (key.IsPressed(DIK_RETURN) == true)
	{
		if (manager.CanSupport(now_pos) == true && manager.GetCellState(now_pos) == CellState::Invisible)
		{
			Invert(manager,now_pos);
			PlayerChange(manager,ui);
		}
	}
}
