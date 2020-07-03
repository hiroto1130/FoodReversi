#ifndef GMAE_MANAGER_H
#define GMAE_MANAGER_H

#include "../Object/CellManager.h"

class GameManager
{
public:

	GameManager() { Initialize(); }
	~GameManager() { Delete(); }

	/**
	 * Update関数をここで呼ぶ
	 */
	void Update();

	/**
	 * Draw関数をここで呼ぶ
	 */
	void Drow();

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

	CellManager* manager = nullptr;

};


#endif
