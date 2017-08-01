#include "GUITextureReader.hpp"

GUITextureReader::GUITextureReader() {}

GUITextureReader::~GUITextureReader() {}

bool GUITextureReader::load()
{
	return loadWindow("assets/gui/window.png");
}

bool GUITextureReader::loadWindow(string filename)
{
	Image sheet;

	if(sheet.loadFromFile(filename))
	{
		if(sheet.getSize().x == 16 && sheet.getSize().y == 16)
		{
			windowTextures[0].loadFromImage(sheet, IntRect(0, 0, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(5, 0, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(10, 0, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(0, 5, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(5, 5, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(10, 5, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(0, 10, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(5, 10, 6, 6));
			windowTextures[0].loadFromImage(sheet, IntRect(10, 10, 6, 6));
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
