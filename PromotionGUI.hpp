#ifndef PROMOTIONGUI_HPP
#define PROMOTIONGUI_HPP

#include "GUIWindow.hpp"
#include "ChessTextureReader.hpp"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class PromotionGUI
{
	public:
		PromotionGUI();
		PromotionGUI(ChessTextureReader*, bool, Vector2u);
		~PromotionGUI();
		void render(RenderWindow*);

	protected:
		Sprite promotionSprite;
		Image promotionImage;
		Texture promotionTexture;
		GUIWindow gWindow;
};

#endif
