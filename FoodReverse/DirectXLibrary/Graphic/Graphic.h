#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <Windows.h>
#include <tchar.h>
#include <d3dx9.h>

#include "..//Device/Device.h"
#include "../Utility/Position.h"
#include "../Utility/RectSize.h"
#include "../Utility/Uv.h"

using Utility::Position;
using Utility::RectSize;
using Utility::Uv;

namespace Library
{
	class TextureData
	{
	public:

		TextureData(LPDIRECT3DTEXTURE9 m_pTexture, Position position, RectSize TextureSize, Uv uv) : m_pTexture(m_pTexture),position(position),texture_size(TextureSize),uv(uv) {}

		LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
		Position position;
		RectSize texture_size;
		Uv uv;

	};

	class MapChipData
	{
	public:

		MapChipData(LPDIRECT3DTEXTURE9 m_pTexture, RectSize TextureSize, RectSize ChipSize) : m_pTexture(m_pTexture), texture_size(TextureSize), chip_size(ChipSize) {}

		LPDIRECT3DTEXTURE9 m_pTexture = nullptr;
		RectSize texture_size;
		RectSize chip_size;
	};

	struct CUSTOMVERTEX
	{
		float	// 頂点座標
			x,  // 幅
			y,  // 高さ
			z;  // 奥行

		float   // 除算数
			rhw;

		float   // テクスチャ座標
			tu,  // 幅
			tv;	// 高さ
	};

	class Texture
	{
	public:

		void Draw(const TextureData& texture_data);
		void Load(const char* file_name, LPDIRECT3DTEXTURE9* Texture);
		void DrawMapChip(const MapChipData map_data, const int* MapChipList[], const int height_number, const int widht_number);

	private:

		void DrawMap(MapChipData map_chip_data, Position chip_uv, Position draw_pos);

	};
}

#endif
