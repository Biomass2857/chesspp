#include "ChessTextureReader.hpp"

ChessTextureReader::ChessTextureReader() {}

ChessTextureReader::~ChessTextureReader() {}

bool ChessTextureReader::load(string filename)
{
	Image sheet;
	
	if(sheet.loadFromFile(filename))
	{
		if(sheet.getSize().x == 7 * SSLEN && sheet.getSize().y == 2 * SSLEN)
		{
			for(int dy = 0; dy < 2; dy++)
			{
				for(int dx = 0; dx < 7; dx++)
				{
					Texture ttexture;
					ttexture.loadFromImage(sheet, IntRect(SSLEN * dx, SSLEN * dy, SSLEN, SSLEN));
					textures.push_back(ttexture);
				}
			}
		}
		else
			return false;
	}
	else
		return false;
		
	return true;
}

Texture& ChessTextureReader::get(char selector, bool sw)
{
	size_t pos = 0;
	
	switch(selector)
	{
		case 'f':
			pos = 0;
		break;
		case 'b':
			pos = 1;
		break;
		case 't':
			pos = 2;
		break;
		case 'p':
			pos = 3;
		break;
		case 'l':
			pos = 4;
		break;
		case 'd':
			pos = 5;
		break;
		case 'k':
			pos = 6;
		break;
	}
	
	if(sw)
		pos += 7;
		
	return textures.at(pos);
}
