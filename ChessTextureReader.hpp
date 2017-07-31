#ifndef CHESSTEXTUREREADER_HPP
#define CHESSTEXTUREREADER_HPP
#define SSLEN 16
#include <iostream>
#include <vector>
#include <strings.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ChessTextureReader
{
	public:
		
		ChessTextureReader();
		~ChessTextureReader();
		
		bool load(string);
		
		Texture& get(char, bool);
		
	protected:
		vector<Texture> textures;
};

#endif
