#ifndef CELL_H
#define CELL_H

#include <vector>

#include "../../Utility/CellState.h"
#include "../../Utility/Direction.h"

class Cell
{
public:

	CellState GetState() { return state; };

	void SetState(CellState chang_state) { state = chang_state; };

	std::vector<int> GetCanInvertDirection() { return can_invert_direction; }

	void SetCanInvertDirection(std::vector<int> direction)
	{
		can_invert_direction.clear();
		can_invert_direction = direction;
	}
private:

	CellState state = CellState::Invisible;

	std::vector<int> can_invert_direction;

};

#endif
