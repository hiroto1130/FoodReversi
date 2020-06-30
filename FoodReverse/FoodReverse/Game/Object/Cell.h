#ifndef NEW_H
#define NEW_H

#include "../../Utility/CellState.h"

class Cell
{
public:

	CellState GetState() { return state; };

	void SetState(CellState chang_state) { state = chang_state; };

private:

	CellState state = CellState::Invisible;

};

#endif
