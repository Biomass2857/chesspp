#ifndef GUIWINDOW_HPP
#define GUIWINDOW_HPP

#include "GUITextureReader.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GUIWindow
{
	public:
		GUIWindow();
		GUIWindow(Sprite, Vector2u, bool = false);
		~GUIWindow();

		void setCentered(bool);

		void setSprite(Sprite);
		Sprite getSprite();

		void render(RenderWindow*);

		void show();
		void hide();
		void toggle();

	protected:
		void recalculateSprites();
		static Texture textures[9];
		static bool texturesLoaded;
		Sprite sprite;
		Vector2f pos;
		Sprite sprites[9];
		Vector2u windSize;
		Sprite bgSprite;
		Texture bgTexture;
		Image bgImage;
		bool isOpen;
		bool isCentered;
};

#endif
