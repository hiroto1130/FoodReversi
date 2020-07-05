#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

#include "../Object/CellManager.h"

class GameSystem
{
public:

	void Invert(CellManager manager, int cell_num);

	void Search();

	void Support();

private:

	int check_list_[8][2] =
	{
		{ 0,-8},
		{ 0, 8},
		{ 1, 0},
		{-1, 0},
		{ 1,-8},
		{-1,-8},
		{ 1, 8},
		{-1, 8}
	};
};

#endif
