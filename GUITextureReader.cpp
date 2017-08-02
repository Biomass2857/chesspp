#include "GUITextureReader.hpp"
#include <iostream>

GUITextureReader::GUITextureReader() {}

GUITextureReader::~GUITextureReader() {}

bool GUITextureReader::windowTexturesLoaded = false;
Texture GUITextureReader::windowTextures[10];

Texture* GUITextureReader::getWindowTextures()
{
	if(!windowTexturesLoaded){

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
		if(!windowTextures[9].loadFromFile("assets/gui/window_overlay.png"))
		{
			std::cout << "Failed to load" << '\n';
		}
	}

	return windowTextures;
}
