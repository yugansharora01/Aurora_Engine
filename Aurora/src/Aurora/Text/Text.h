#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Platform/DirectX/D3D11Texture.h"

namespace Aurora
{
	class Text
	{
	public:
		std::vector<unsigned char> image;
		unsigned int Pitch;
		FT_GlyphSlot slot;
	public:
		Text();
		~Text();
		void draw_bitmap(FT_Bitmap* bitmap);
		void show_image();
		Ref<D3D11Texture> get();
	private:
		FT_Library    library;
		FT_Face       face;
	};

}

