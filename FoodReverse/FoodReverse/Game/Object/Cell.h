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

	std::vector<Direction> GetCanInvertDirection() { return can_invert_direction; }

	void SetCanInvertDirection(std::vector<Direction> direction) { can_invert_direction = direction; }

private:

	CellState state = CellState::Invisible;

	std::vector<Direction> can_invert_direction;

};

#endif
