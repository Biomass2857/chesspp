#include "GUIWindow.hpp"
#include <iostream>

GUIWindow::GUIWindow() {}

void GUIWindow::init(Sprite& sprite_, Vector2u windS, bool dark, bool center)
{
	isOpen = false;
	isCentered = center;
	windSize = windS;
	Texture* textures = GUITextureReader::getWindowTextures(dark);
	for(char i = 0; i < 9; i++)
	{
		sprites[i].setTexture(*(textures + i));
	}
	Texture& bgTexture = *(textures + 9);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(windSize.x / bgTexture.getSize().x, windSize.y / bgTexture.getSize().y);
	bgSprite.setPosition(0, 0);

	setSprite(&sprite_);
}

GUIWindow::~GUIWindow() {}

void GUIWindow::render(RenderWindow *w)
{
	if(isOpen)
	{
		w->draw(bgSprite);
		for(char i = 0; i < 9; i++)
		{
			w->draw(sprites[i]);
		}
		w->draw(*sprite);
	}
}

void GUIWindow::setSprite(Sprite* value)
{
	sprite = value;
	pos = sprite->getPosition();
	recalculateSprites();
}

Sprite* GUIWindow::getSprite()
{
	return sprite;
}

void GUIWindow::recalculateSprites()
{
	Vector2f corner = Vector2f(6/RES, 6/RES);
	Vector2f scale = sprite->getScale();
	Vector2f bounds = Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height);

	float centerx = isCentered ? bounds.x / 2 : 0;
	float centery = isCentered ? bounds.y / 2 : 0;
	float posx[3] = {pos.x - windSize.x / RES * 6 - centerx, pos.x - centerx, pos.x + bounds.x - centerx};
	float posy[3] = {pos.y - windSize.y / RES * 6 - centery, pos.y - centery, pos.y + bounds.y - centery};
	float scalex[3] = {float(windSize.x / RES), float(bounds.x) / 6, float(windSize.x / RES)};
	float scaley[3] = {float(windSize.y / RES), float(bounds.y) / 6, float(windSize.y / RES)};

	for(char i = 0; i < 9; i++)
	{
		char x = i % 3;
		char y = i / 3;
		sprites[i].setPosition(Vector2f(posx[x], posy[y]));
		sprites[i].setScale(Vector2f(scalex[x], scaley[y]));
	}

}

void GUIWindow::show()
{
	isOpen = true;
}

void GUIWindow::hide()
{
	isOpen = false;
}

void GUIWindow::toggle()
{
	isOpen = !isOpen;
}

void GUIWindow::setCentered(bool value)
{
	isCentered = value;
}
