#ifndef SKIN_H
#define SKIN_H

#include <map>
#include <string>
#include <vector>

#include "../../DirectXLibrary/Graphic/Graphic.h"

enum class SkinName
{
	Sushi,
	Cake,
	Normal
};

namespace ElementName
{
	const int Background = 0;
	const int Motion = 1;
	const int Black_Count = 2;
	const int White_Coun = 3;
};

class Skin
{
public:
	Skin(const Skin&) = delete;
	Skin& operator=(const Skin&) = delete;
	Skin(Skin&&) = delete;
	Skin& operator=(Skin&&) = delete;

	static inline Skin& get_instance() {
		return *instance;
	}

	static inline void create() {
		if (!instance) {
			instance = new Skin;
		}
	}

	static inline void destroy() {
		delete instance;
		instance = nullptr;
	}

	inline void SetSkin(SkinName name) { SelectSkin = name; }

	inline std::vector<Uv> GetSkinTextureList()
	{
		return SkinSelect();
	}

private:

	Skin() = default;
	~Skin() = default;

	static Skin* instance;

	std::vector<Uv> SkinSelect();

	SkinName SelectSkin = SkinName::Normal;
	
	// tu 横 tv 縦                    Background      Motion           Black_Coun      White_Coun
	std::vector<Uv> sushi_uv_pos  = { Uv(0,0.5,0.5,1),Uv(0,0.75,1,1)  ,Uv(0,0.5,0.5,1),Uv(0,0.5,0.5,1) };
	std::vector<Uv> cake_uv_pos   = { Uv(0.5,0,1,0.5),Uv(0,0.5,1,0.75),Uv(0,0,0.5,0.5),Uv(0,0,0.5,0.5) };
	std::vector<Uv> normal_uv_pos = { Uv(0,0,0.5,0.5),Uv(0,0.25,1,0.5),Uv(0,0,0.5,0.5),Uv(0,0,0.5,0.5) };
};

#endif
