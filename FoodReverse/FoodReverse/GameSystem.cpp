#include "Game\System\GameSystem.h"

namespace
{
	const int UP = 0;
	const int DOWN = 1;
	const int RIGHT = 2;
	const int LEFT = 3;
	const int UP_RIGHT = 4;
	const int UP_LEFT = 5;
	const int DOWN_RIGHT = 6;
	const int DOWN_LEFT = 7;
	const int ADD_X = 0;
	const int ADD_Y = 1;

	const int MAX_CELL = 64;
	const int MIN_CELL = 0;
}

void GameSystem::Invert(CellManager manager, int cell_num)
{
	std::vector<int> invert_direction = manager.GetSupprt(cell_num);

	int x = 0, y = 0, next_cell = 0, int repeat_count = 0;

	CellState invert_color = manager.GetState(cell_num);

	for (auto direction : invert_direction)
	{
		x = check_list_[direction][ADD_X];
		y = check_list_[direction][ADD_Y];

		while (true)
		{
			++repeat_count;
			next_cell = (x * repeat_count) + (y * repeat_count) + cell_num;

			if (manager.GetState(next_cell) == CellState::Invisible)
			{
				manager.SetState(invert_color, next_cell);
				break;
			}

			manager.SetState(invert_color, next_cell);
		}
	}
}

void GameSystem::Search()
{
}

void GameSystem::Support()
{
}
