#include "pch.h"
#include "Text.h"
#include "Aurora/Core/Log.h"

namespace Aurora
{
	Text::Text()
	{
		

		//-----------------------------------------------------------------------------------
		

		
		FT_Matrix     matrix;                 /* transformation matrix */
		FT_Vector     pen;                    /* untransformed origin  */
		FT_Error      error;

		const char* filename = "D:\\yash\\my-work\\engine\\Aurora-Editor\\assets\\Text-files\\Cursive-like-font.ttf";
		const char* text = "A";

		double        angle;
		int           target_height;
		int           n, num_chars;

		num_chars = strlen(text);
		angle = (25.0 / 360) * 3.14159 * 2;      /* use 25 degrees     */
		target_height = 480;

		error = FT_Init_FreeType(&library);              /* initialize library */
  /* error handling omitted */
		if (error)
		{
			AU_ERROR("FT_Init_FreeType");
			std::cout << "passed FT_Init_FreeType";
		}

		error = FT_New_Face(library, filename, 0, &face);/* create face object */
		/* error handling omitted */

		if (error)
		{
			AU_ERROR("FT_New_Face");
			std::cout << "passed FT_New_Face";
		}

		error = FT_Set_Char_Size(face, 50 * 64, 0,
			100, 0);                /* set character size */
		if (error)
		{
			AU_ERROR("FT_Set_Char_Size");
			std::cout << "passed FT_Set_Char_Size";
		}

/* cmap selection omitted;                                        */
/* for simplicity we assume that the font contains a Unicode cmap */

		slot = face->glyph;

		/* set up matrix */
		matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
		matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
		matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
		matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

		/* the pen position in 26.6 cartesian space coordinates; */
		/* start at (300,200) relative to the upper left corner  */
		pen.x = 300 * 64;
		pen.y = (target_height - 200) * 64;

		for (n = 0; n < num_chars; n++)
		{
			/* set transformation */
			FT_Set_Transform(face, &matrix, &pen);

			/* load glyph image into the slot (erase previous one) */
			error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
			if (error)
			{
				AU_ERROR("FT_Load_Char");                 
				std::cout << "passed FT_Load_Char";
			}

			  /* now, draw to our target surface (convert position) */
			draw_bitmap(&slot->bitmap);

			/* increment pen position */
			pen.x += slot->advance.x;
			pen.y += slot->advance.y;
		}




		//auto slot = face->glyph;
		//draw_bitmap(&slot->bitmap,
		//	slot->bitmap_left,
		//	target_height - slot->bitmap_top);

		//show_image();
		
		
	}

	Text::~Text()
	{
		FT_Done_Face(face);
		FT_Done_FreeType(library);
	}

	void Text::draw_bitmap(FT_Bitmap* bitmap)
	{
		for (int i = 0; i < bitmap->rows; i++)
		{
			for (int j = 0; j < bitmap->pitch; j++)
			{
				image.push_back(bitmap->buffer[i * bitmap->pitch + j]);
			}
		}
		Pitch = bitmap->width;
	}

	void Text::show_image(void)
	{
		int  i, j;


		for (i = 0; i < 480; i++)
		{
			for (j = 0; j < 480; j++)
				putchar(image[i]);
				//putchar(image[i][j] == 0 ? ' '
				//	: image[i][j] < 128 ? '+'
				//	: '*');
			putchar('\n');
		}
	}
	Ref<D3D11Texture> Text::get()
	{
		return CreateRef<D3D11Texture>(image.data(),Pitch);
	}
}