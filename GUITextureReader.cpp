#include "GUITextureReader.hpp"
#include <iostream>

GUITextureReader::GUITextureReader() {}

GUITextureReader::~GUITextureReader() {}

bool GUITextureReader::windowTexturesLoaded = false;
bool GUITextureReader::windowTexturesDarkLoaded = false;
Texture GUITextureReader::windowTextures[10];
Texture GUITextureReader::windowTexturesDark[10];

bool GUITextureReader::menuTexturesLoaded = false;
Texture GUITextureReader::menuTextures[1];

bool GUITextureReader::fontLoaded = false;
Font GUITextureReader::font;

Texture* GUITextureReader::getWindowTextures(bool dark)
{
	if(!dark)
	{
		if(!windowTexturesLoaded)
		{
			Image sheet;

			if(sheet.loadFromFile("assets/gui/window.png"))
			{
				if(sheet.getSize().x == 16 && sheet.getSize().y == 16)
				{
					windowTextures[0].loadFromImage(sheet, IntRect(0, 0, 6, 6));
					windowTextures[1].loadFromImage(sheet, IntRect(5, 0, 6, 6));
					windowTextures[2].loadFromImage(sheet, IntRect(10, 0, 6, 6));
					windowTextures[3].loadFromImage(sheet, IntRect(0, 5, 6, 6));
					windowTextures[4].loadFromImage(sheet, IntRect(5, 5, 6, 6));
					windowTextures[5].loadFromImage(sheet, IntRect(10, 5, 6, 6));
					windowTextures[6].loadFromImage(sheet, IntRect(0, 10, 6, 6));
					windowTextures[7].loadFromImage(sheet, IntRect(5, 10, 6, 6));
					windowTextures[8].loadFromImage(sheet, IntRect(10, 10, 6, 6));
				}
				for(char i = 0; i < 9; i++)
				{
					windowTextures[i].setRepeated(true);
				}
			}
			windowTextures[9].loadFromFile("assets/gui/window_overlay.png");
		}
		return windowTextures;
	}
	else
	{
		if(!windowTexturesDarkLoaded)
		{
			Image sheet;

			if(sheet.loadFromFile("assets/gui/window_dark.png"))
			{
				if(sheet.getSize().x == 16 && sheet.getSize().y == 16)
				{
					windowTexturesDark[0].loadFromImage(sheet, IntRect(0, 0, 6, 6));
					windowTexturesDark[1].loadFromImage(sheet, IntRect(5, 0, 6, 6));
					windowTexturesDark[2].loadFromImage(sheet, IntRect(10, 0, 6, 6));
					windowTexturesDark[3].loadFromImage(sheet, IntRect(0, 5, 6, 6));
					windowTexturesDark[4].loadFromImage(sheet, IntRect(5, 5, 6, 6));
					windowTexturesDark[5].loadFromImage(sheet, IntRect(10, 5, 6, 6));
					windowTexturesDark[6].loadFromImage(sheet, IntRect(0, 10, 6, 6));
					windowTexturesDark[7].loadFromImage(sheet, IntRect(5, 10, 6, 6));
					windowTexturesDark[8].loadFromImage(sheet, IntRect(10, 10, 6, 6));
				}
				for(char i = 0; i < 9; i++)
				{
					windowTexturesDark[i].setRepeated(true);
				}
			}
			windowTexturesDark[9].loadFromFile("assets/gui/window_overlay.png");
		}
		return windowTexturesDark;
	}
}

Texture* GUITextureReader::getMenuTextures()
{
	if(!menuTexturesLoaded)
	{
		menuTextures[0].loadFromFile("assets/gui/menu_bg.png");
	}
	return menuTextures;
}

Font* GUITextureReader::getFont()
{
	if(!fontLoaded)
	{
		font.loadFromFile("assets/font/joystix monospace.ttf");
	}
	return &font;
}
