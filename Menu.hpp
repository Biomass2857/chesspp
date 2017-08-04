#ifndef MENU_HPP
#define MENU_HPP
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"
#include "GUITextureReader.hpp"
#include "GUIWindow.hpp"
#include "util.hpp"

using namespace std;
using namespace sf;

class Menu
{
	public:
		Menu();
		~Menu();

		void init(Vector2u);

		void render(RenderWindow*);

		void handleLeftClickPressed(Event, RenderWindow*);

	protected:
		ChessTextureReader texturePack;

		void updateSessionButtons(Vector2u);
		void updateColorButtons(Vector2u);

		char menuState;
		Texture* textures;
		Font* font;

		Sprite backgroundSprite;

		Text titleText;

		GUIWindow clientButton;
		Text clientText;
		Sprite clientSprite;
		GUIWindow hostButton;
		Text hostText;
		Sprite hostSprite;
		Image transparentImage;
		Texture transparentTexture;

		GUIWindow whiteButton;
		Sprite whiteSprite;
		GUIWindow blackButton;
		Sprite blackSprite;

		SessionType sessionType;
		bool ownColor;

};

#endif
