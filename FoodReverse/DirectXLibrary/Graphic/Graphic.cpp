#include "Graphic.h"
namespace Library
{
	void Texture::Draw(const TextureData& texture_data)
	{
		float x = texture_data.position.x;
		float y = texture_data.position.y;

		float width = texture_data.texture_size.width;
		float height = texture_data.texture_size.height;

		float tu = texture_data.uv.tu;
		float tv = texture_data.uv.tv;
		float tu_size = texture_data.uv.tu_size;
		float tv_size = texture_data.uv.tv_size;

		CUSTOMVERTEX customvertex[4] = {
		{ x         , y          , 0 , 1 , tu      , tv      },
		{ x + width , y          , 0 , 1 , tu_size , tv      },
		{ x + width , y + height , 0 , 1 , tu_size , tv_size },
		{ x         , y + height , 0 , 1 , tu      , tv_size },
		};

		LPDIRECT3DDEVICE9 pDevice;
		Device::GetWindowHandle(&pDevice);

		pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
		pDevice->SetTexture(0,texture_data.m_pTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, customvertex, sizeof(CUSTOMVERTEX));


	}

	void Texture::Load(const char* file_name, LPDIRECT3DTEXTURE9* Texture)
	{
		LPDIRECT3DDEVICE9 pDevice;
		Device::GetWindowHandle(&pDevice);

		HRESULT result = D3DXCreateTextureFromFile(pDevice, file_name, Texture);

		if ((_D3DXERR)result == D3DXERR_INVALIDDATA)
		{
			OutputDebugString(TEXT("\nテクスチャファイルが見つかりません\n"));
		}
	}

	void Texture::DrawMapChip(const MapChipData map_chip_data, const int* MapChipList[], const int height_number, const int widht_number)
	{
		for (int now_height_number = 0; now_height_number < height_number; now_height_number++)
		{
			for (int now_width_number = 0; now_width_number < widht_number; now_width_number++)
			{
				int chip_id = MapChipList[now_height_number][now_width_number];

				int width_num = static_cast<int>(map_chip_data.texture_size.width / map_chip_data.chip_size.width);
				int height_num = static_cast<int>(map_chip_data.texture_size.height / map_chip_data.chip_size.height);

				float chip_x = static_cast<float>(((chip_id % width_num) * map_chip_data.chip_size.width));
				float chip_y = static_cast<float>(((chip_id / height_num) * map_chip_data.chip_size.height));
				Position chip_pos{ chip_x,chip_y };

				float draw_x = (map_chip_data.chip_size.width * now_width_number);
				float draw_y = (map_chip_data.chip_size.height * now_height_number);
				Position draw_pos{ draw_x,draw_y };

				DrawMap(map_chip_data,chip_pos,draw_pos);

			}

		}

	}

	void Texture::DrawMap(MapChipData map_chip_data, Position chip_pos, Position draw_pos)
	{
		float cx = chip_pos.x / map_chip_data.texture_size.width;
		float cy = chip_pos.y / map_chip_data.texture_size.height;
		
		float cx_size = map_chip_data.chip_size.width / map_chip_data.texture_size.width;
		float cy_size = map_chip_data.chip_size.height / map_chip_data.texture_size.height;

		float cu_size = cx + cx_size;
		float cv_size = cy + cy_size;

		CUSTOMVERTEX sprite[] =
		{
			{ draw_pos.x                                 , draw_pos.y                                 , 0.0f, 1.0f , cx      ,cy      },
			{ draw_pos.x + map_chip_data.chip_size.width , draw_pos.y                                 , 0.0f, 1.0f , cu_size  ,cy      },
			{ draw_pos.x + map_chip_data.chip_size.width , draw_pos.y + map_chip_data.chip_size.height, 0.0f, 1.0f , cu_size  ,cv_size  },
			{ draw_pos.x                                 , draw_pos.y + map_chip_data.chip_size.height, 0.0f, 1.0f , cx      ,cv_size  },
		};

		LPDIRECT3DDEVICE9 pDevice;
		Device::GetWindowHandle(&pDevice);

		pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
		pDevice->SetTexture(0, map_chip_data.m_pTexture);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, sprite, sizeof(CUSTOMVERTEX));
	}

}
