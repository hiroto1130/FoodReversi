#include "Skin.h"

Skin* Skin::instance = nullptr;

std::vector<Uv> Skin::SkinSelect()
{
	switch (SelectSkin)
	{
	case SkinName::Sushi:
		return sushi_uv_pos;
		break;
	case SkinName::Cake:
		return cake_uv_pos;
		break;
	case SkinName::Normal:
		return normal_uv_pos;
		break;
	default:
		break;
	}
}