#ifndef GMAE_MANAGER_H
#define GMAE_MANAGER_H

#include "../../../DirectXLibrary/Device/Input/Key.h"

#include "../Object/CellManager.h"
#include "../System/GameSystem.h"
#include "../Ui/Ui.h"
#include "../../Utility/Timer/Timer.h"
#include "../../Save/Save.h"

class GameManager
{
public:

	GameManager() { Initialize(); }
	~GameManager() { Delete(); }

	inline bool GetGameState() 
	{
		return IsGameEnd;
	}

	/**
	 * Update関数をここで呼ぶ
	 */
	void Update(Library::Key& key);

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

	void WinnerDistinction();

	bool IsGameEnd = false;

	bool is_pass = false;

	CellManager* manager = nullptr;
	GameSystem* system = nullptr;
	Ui* ui = nullptr;
	
	Timer* timer = nullptr;
	Save* save = nullptr;
};


#endif
