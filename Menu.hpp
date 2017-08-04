#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include "GUITextureReader.hpp"

using namespace std;
using namespace sf;

class Menu
{
	public:
		Menu();
		~Menu();
		void render(RenderWindow*);

	protected:
		char menuState;

};

#endif
