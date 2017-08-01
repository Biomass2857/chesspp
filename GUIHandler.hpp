#ifndef GUIHANDLER_HPP
#define GUIHANDLER_HPP

#include "GUITextureReader.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GUIHandler {
	public:
		GUIHandler();
		~GUIHandler();

	protected:
		GUITextureReader texturePack;

};

#endif
