#include "GUIWindow.hpp"
#include <iostream>
#define RES 128

GUIWindow::GUIWindow() {}

GUIWindow::GUIWindow(Sprite sprite_, Vector2u windS, bool center) : isOpen(false)
{
	windSize = windS;
	Texture* textures = GUITextureReader::getWindowTextures();
	for(char i = 0; i < 9; i++)
	{
		sprites[i].setTexture(*(textures + i));
	}
	Texture& bgTexture = *(textures + 9);
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(windSize.x / bgTexture.getSize().x, windSize.y / bgTexture.getSize().y);
	bgSprite.setPosition(0, 0);

	setSprite(sprite_);
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
		w->draw(getSprite());
	}
}

void GUIWindow::setSprite(Sprite value)
{
	sprite = value;
	pos = sprite.getPosition();
	recalculateSprites();
}

Sprite GUIWindow::getSprite()
{
	return sprite;
}

void GUIWindow::recalculateSprites()
{
	Vector2f corner = Vector2f(6/128, 6/128);
	Vector2f scale = sprite.getScale();
	Vector2f bounds = Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

	float posx[3] = {pos.x - windSize.x / 128 * 6, pos.x, pos.x + bounds.x};
	float posy[3] = {pos.y - windSize.y / 128 * 6, pos.y, pos.y + bounds.y};
	float scalex[3] = {float(windSize.x / 128), float(bounds.x) / 6, float(windSize.x / 128)};
	float scaley[3] = {float(windSize.y / 128), float(bounds.y) / 6, float(windSize.y / 128)};

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
