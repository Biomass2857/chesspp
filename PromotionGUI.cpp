#include "PromotionGUI.hpp"
#include <iostream>

PromotionGUI::PromotionGUI() {}

void PromotionGUI::init(ChessTextureReader* pieceTexturePack, bool color, Vector2u windSize)
{
	promotionImage.create(64, 16, Color::Transparent);
	promotionImage.copy(pieceTexturePack->textures.at(3 + color * 7).copyToImage(), 0, 0);
	promotionImage.copy(pieceTexturePack->textures.at(4 + color * 7).copyToImage(), 16, 0);
	promotionImage.copy(pieceTexturePack->textures.at(2 + color * 7).copyToImage(), 32, 0);
	promotionImage.copy(pieceTexturePack->textures.at(5 + color * 7).copyToImage(), 48, 0);
	promotionTexture.loadFromImage(promotionImage);
	promotionSprite.setTexture(promotionTexture);
	promotionSprite.setOrigin(promotionImage.getSize().x / 2, promotionImage.getSize().y / 2);
	promotionSprite.setPosition(windSize.x * 0.5, windSize.y * 0.5);
	promotionSprite.setScale(windSize.x / RES, windSize.y / RES);
	gWindow.init(promotionSprite, windSize, !color, true);
	gWindow.show();
}

PromotionGUI::~PromotionGUI() {}

void PromotionGUI::render(RenderWindow* window)
{
	gWindow.render(window);

}

char PromotionGUI::getPieceForPosition(Vector2i mousePos, Vector2u windSize)
{
	if(mousePos.x >= windSize.x * 0.5 - 38 && mousePos.x <= windSize.x * 0.5 + 38 && mousePos.y >= windSize.y * 0.5 - 14 && mousePos.y <= windSize.y * 0.5 + 14)
	{
		if(mousePos.x < windSize.x * 0.5 - 22) return 3;
		if(mousePos.x < windSize.x * 0.5 - 6) return 4;
		if(mousePos.x < windSize.x * 0.5 + 6) return 2;
		return 5;
	}
	return 0;
}

void PromotionGUI::handleLeftClickPressed(RenderWindow* window)
{
	clickPressPiece = getPieceForPosition(Mouse::getPosition(*window), window->getSize());
}

char PromotionGUI::handleLeftClickReleased(RenderWindow* window)
{
	if(clickPressPiece != 0)
	{
		return getPieceForPosition(Mouse::getPosition(*window), window->getSize());
	}
	return 0;
}
