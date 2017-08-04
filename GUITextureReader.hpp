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
		static Texture* getMenuTextures();
		static Font* getFont();

	protected:
		static bool windowTexturesLoaded;
		static bool windowTexturesDarkLoaded;
		static Texture windowTextures[10];
		static Texture windowTexturesDark[10];

		static bool menuTexturesLoaded;
		static Texture menuTextures[1];

		static bool fontLoaded;
		static Font font;
};

#endif
