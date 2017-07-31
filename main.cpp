#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"

using namespace std;
using namespace sf;

int main()
{
	const Vector2u wSize = Vector2u(14 * 48, 14 * 48);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "TextureReaderTest");
	Event event;
	
	ChessTextureReader texturePack;
	
	if(!texturePack.load("spritesheet.png"))
		return -1;
	
	Sprite sprites[14];
	
	for(int i = 0; i < 14; i++)
	{
		sprites[i].setTexture(texturePack.get(i, true));
		
		sprites[i].setScale(3, 3);
		
		sprites[i].setPosition(i* 48, i * 48);
	}
	
	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}
		
		if(window.getSize().x != wSize.x || window.getSize().y != wSize.y)
			window.setSize(wSize);
		
		window.clear(Color::White);
		for(int i = 0; i < 14; i++)
		{
			window.draw(sprites[i]);
		}
		window.display();
	}	
	
	return 0;
}
