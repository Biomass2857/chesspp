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

		static Texture* getWindowTextures();

	protected:
		static bool windowTexturesLoaded;
		static Texture windowTextures[10];
};

#endif
