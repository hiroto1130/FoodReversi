#include  "CellManager.h"

namespace 
{
	const int MAX_CELL = 64;
}
void CellManager::Initialize()
{
	for (int create_cell = 0; create_cell < MAX_CELL; ++create_cell)
	{
		field.push_back(nullptr);
		field[create_cell] = new Cell();
	}
}

void CellManager::Delete()
{
	for (int delete_cell = 0; delete_cell < MAX_CELL; ++delete_cell)
	{
		delete field[delete_cell];
	}
}