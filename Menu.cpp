#include "Menu.hpp"

Menu::Menu() : menuState(0), sessionType(SessionType::CLIENT), ownColor(false)
{

}

Menu::~Menu() {}

void Menu::init(Vector2u windSize)
{
	texturePack.load("assets/pieces.png");

	textures = GUITextureReader::getMenuTextures();

	backgroundSprite.setTexture(textures[0]);
	backgroundSprite.setPosition(0, 0);
	backgroundSprite.setScale(windSize.x / 128, windSize.y / 128);

	font = GUITextureReader::getFont();

	titleText.setFont(*font);
	titleText.setString("Chess++");
	titleText.setFillColor(Color(0, 50, 120));
	titleText.setCharacterSize(windSize.y / 128 * 20);
	titleText.setPosition(windSize.x * 0.5, windSize.y / 128 * 15);
	FloatRect g = titleText.getGlobalBounds();
	titleText.setOrigin(g.width * 0.5, g.height * 0.5);

	transparentImage.create(1, 1, Color::Transparent);
	transparentTexture.loadFromImage(transparentImage);
	clientText.setFont(*font); hostText.setFont(*font);
	unsigned int size = windSize.y / 128 * 5;
	clientText.setCharacterSize(size); hostText.setCharacterSize(size);
	clientText.setString("Client"); hostText.setString("Host");
	FloatRect bounds[2]; bounds[0] = clientText.getGlobalBounds(); bounds[1] = hostText.getGlobalBounds();
	float width = bounds[0].width + windSize.x * 0.1 + bounds[1].width;
	clientText.setPosition((windSize.x - width) / 2, windSize.y / 128 * 50);
	hostText.setPosition((windSize.x + width) / 2, windSize.y / 128 * 50);
	clientText.setOrigin(bounds[0].width * 0.5, bounds[0].height * 0.6); hostText.setOrigin(bounds[1].width * 0.5, bounds[0].height * 0.6);
	clientSprite.setTexture(transparentTexture); hostSprite.setTexture(transparentTexture);
	clientSprite.setScale(bounds[0].width, bounds[0].height); hostSprite.setScale(bounds[1].width, bounds[1].height);
	clientSprite.setPosition(clientText.getPosition()); hostSprite.setPosition(hostText.getPosition());
	updateSessionButtons(windSize);

	whiteSprite.setTexture(texturePack.textures[1]);
	blackSprite.setTexture(texturePack.textures[8]);
	whiteSprite.setScale(windSize.x / 128, windSize.y / 128); blackSprite.setScale(windSize.x / 128, windSize.y / 128);
	whiteSprite.setPosition(windSize.x / 2 - windSize.x / 128 * 16, windSize.y / 128 * 90);
	blackSprite.setPosition(windSize.x / 2 + windSize.x / 128 * 16, windSize.y / 128 * 90);
	whiteSprite.setOrigin(8, 8); blackSprite.setOrigin(8, 8);
	updateColorButtons(windSize);
}

void Menu::render(RenderWindow* window)
{
	window->draw(backgroundSprite);
	switch(menuState)
	{
		case 0:
			clientButton.render(window); hostButton.render(window);
			window->draw(titleText);
			window->draw(clientText);
			window->draw(hostText);
			whiteButton.render(window); blackButton.render(window);
			break;
		case 1:

			break;
	}
}

void Menu::handleEvent(Event event, RenderWindow* window)
{
    if(event.mouseButton.button == Mouse::Button::Left){
        Vector2i mousePos = Mouse::getPosition(*window);
        if(clientButton.isInbound(mousePos))
            sessionType = SessionType::CLIENT;
        if(hostButton.isInbound(mousePos))
            sessionType = SessionType::HOST;
        updateSessionButtons(window->getSize());
        if(whiteButton.isInbound(mousePos))
            ownColor = false;
        if(blackButton.isInbound(mousePos))
            ownColor = true;
        updateColorButtons(window->getSize());
    }
}

void Menu::updateSessionButtons(Vector2u windSize)
{
	if(sessionType == SessionType::HOST)
	{
		clientText.setFillColor(Color(0, 50, 120)); hostText.setFillColor(Color(255, 237, 151));
		clientButton.init(clientSprite, windSize, false, true, true, false);
		hostButton.init(hostSprite, windSize, true, true, true, false);
	}
	else
	{
		clientText.setFillColor(Color(255, 237, 151)); hostText.setFillColor(Color(0, 50, 120));
		clientButton.init(clientSprite, windSize, true, true, true, false); hostButton.init(hostSprite, windSize, false, true, true, false);
	}
}

void Menu::updateColorButtons(Vector2u windSize)
{
	if(ownColor)
	{
		whiteButton.init(whiteSprite, windSize, false, true, true, false);
		blackButton.init(blackSprite, windSize, true, true, true, false);
	}
	else
	{
		whiteButton.init(whiteSprite, windSize, true, true, true, false);
		blackButton.init(blackSprite, windSize, false, true, true, false);
	}
}
