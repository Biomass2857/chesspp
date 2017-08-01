#include "GUITextureReader.hpp"

GUITextureReader::GUITextureReader() {}

GUITextureReader::~GUITextureReader() {}

bool GUITextureReader::getWindowTextures(string filename, Texture* textures)
{
	Image sheet;

	if(sheet.loadFromFile(filename))
	{
		if(sheet.getSize().x == 16 && sheet.getSize().y == 16)
		{
			textures->loadFromImage(sheet, IntRect(0, 0, 6, 6));
			(textures + 1)->loadFromImage(sheet, IntRect(5, 0, 6, 6));
			(textures + 2)->loadFromImage(sheet, IntRect(10, 0, 6, 6));
			(textures + 3)->loadFromImage(sheet, IntRect(0, 5, 6, 6));
			(textures + 4)->loadFromImage(sheet, IntRect(5, 5, 6, 6));
			(textures + 5)->loadFromImage(sheet, IntRect(10, 5, 6, 6));
			(textures + 6)->loadFromImage(sheet, IntRect(0, 10, 6, 6));
			(textures + 7)->loadFromImage(sheet, IntRect(5, 10, 6, 6));
			(textures + 8)->loadFromImage(sheet, IntRect(10, 10, 6, 6));
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}
