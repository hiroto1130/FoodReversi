#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Cell.h"

class Board
{
public:
	Board() { Initialize(); }
	~Board() { Delete(); }


private:

	/**
	 * 初期化関数
	 */
	void Initialize();

	/**
	 * 削除関数
	 * @detail デストラクタで呼び、delete処理をメインで行う
	 */
	void Delete();

	std::vector<Cell*> field;

};

#endif
