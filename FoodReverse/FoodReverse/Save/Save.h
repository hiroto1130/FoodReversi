#ifndef SAVE_H
#define SAVE_H

#include <vector>

#include "../Game/Object/CellManager.h"
#include "../Utility/CellState.h"
#include "../Utility/Player.h"

class Save
{
public:
	Save(const Save&) = delete;
	Save& operator=(const Save&) = delete;
	Save(Save&&) = delete;
	Save& operator=(Save&&) = delete;

	static inline Save& get_instance() {
		return *instance;
	}

	static inline void create() {
		if (!instance) {
			instance = new Save;
		}
	}

	static inline void destroy() {
		delete instance;
		instance = nullptr;
	}

	inline void SetLastFiled(CellManager& manager)
	{
		std::vector<Cell*> filed = manager.GetField();
		last_field_state.clear();
		for (int cell_num = 0; cell_num < 64; ++cell_num)
		{
			last_field_state.push_back(filed[cell_num]->GetState());
		}
	}

	inline std::vector<CellState> GetLastField()
	{
		return last_field_state;
	}

	inline void SetWinner(Player player)
	{
		winner = player;
	}

	inline Player GetWinner()
	{
		return winner;
	}

private:

	Save() = default;
	~Save() = default;

	static Save* instance;

	std::vector<CellState> last_field_state;

	Player winner;

};

#endif
