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
		void init(ChessTextureReader*, bool, Vector2u);
		~PromotionGUI();
		void render(RenderWindow*);
		char getPieceForPosition(Vector2i, Vector2u);
		void handleLeftClickPressed(RenderWindow*);
		
		char getCurrentPiece();
		// dont get it
		char handleLeftClickReleased(RenderWindow*);

	protected:
		Sprite promotionSprite;
		Image promotionImage;
		Texture promotionTexture;
		GUIWindow gWindow;
		char clickPressPiece;
};

#endif
