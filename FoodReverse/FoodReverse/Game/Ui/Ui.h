#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <map>

#include "../../../DirectXLibrary/Graphic/Graphic.h"

#include "../../Utility/StoneCount.h"
#include "../../Utility/Player.h"
#include "../../Skin/Skin.h"
#include "../../Utility/Timer/Timer.h"

class Ui
{
public:
	
	Ui() { Initialize(); }
	~Ui() { Delete(); }

	void Draw(bool is_pass);

	void Update();

	inline void SetStoneCount(StoneCount conut)
	{
		stoneConut = conut;
	}

	inline void SetNowPlayer(Player player)
	{
		now_player = player;
	}

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

	void DrawNumber();

	Position playerUiPos_1 = Position(1520, 885);
	Position playerUiPos_2 = Position(46, 395);

	int motion_count = 0;

	StoneCount stoneConut;

	Player now_player = Player::Player_1;

	Skin* skin = nullptr;

	Timer* motion_timer = nullptr;

	Library::Texture* texture = nullptr;
	std::vector<Library::TextureData*> textureData;
};

#endif
