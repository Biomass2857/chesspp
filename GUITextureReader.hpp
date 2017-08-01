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

		bool load();

		bool loadWindow(string);

		Texture windowTextures[9];

	protected:

};

#endif
