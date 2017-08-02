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
