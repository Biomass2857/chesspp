#include "GUIWindow.hpp"
#include <iostream>
#define RES 128

GUIWindow::GUIWindow() {}

GUIWindow::GUIWindow(Sprite sprite_, Vector2u windS)
{
	windSize = windS;
	if(!texturesLoaded)
	{
		GUITextureReader::getWindowTextures("assets/gui/window.png", textures);
	}
	for(char i = 0; i < 9; i++)
	{
		textures[i].setRepeated(true);
		sprites[i].setTexture(textures[i]);
	}

	bgTexture.loadFromFile("assets/gui/overlay.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(128 / 32, 128 / 32);
	bgSprite.setPosition(0, 0);

	setSprite(sprite_);
}

GUIWindow::~GUIWindow() {}

void GUIWindow::render(RenderWindow *w)
{
	w->draw(bgSprite);
	for(char i = 0; i < 9; i++)
	{
		w->draw(sprites[i]);
	}
	w->draw(getSprite());
}

bool GUIWindow::texturesLoaded = false;
Texture GUIWindow::textures[9];

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

	float posx[3] = {pos.x - windSize.x / 128 * 6, pos.x, pos.x + bounds.x/* - windSize.x / 128 * 6*/};
	float posy[3] = {pos.y - windSize.y / 128 * 6, pos.y, pos.y + bounds.y/* - windSize.y / 128 * 6*/};
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
