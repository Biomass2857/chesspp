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

		static bool getWindowTextures(string, Texture*);

	protected:

};

#endif
