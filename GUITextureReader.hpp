#ifndef GUITEXTUREREADER_HPP
#define GUITEXTUREREADER_HPP

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GUITextureReader
{
	public:
		GUITextureReader();
		~GUITextureReader();

		static Texture* getWindowTextures(bool = false);

	protected:
		static bool windowTexturesLoaded;
		static bool windowTexturesDarkLoaded;
		static Texture windowTextures[10];
		static Texture windowTexturesDark[10];
};

#endif
