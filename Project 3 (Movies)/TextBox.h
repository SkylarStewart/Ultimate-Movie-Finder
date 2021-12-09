#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class TextBox
{
	sf::RectangleShape boxSprite;
	sf::Text boxText;

public:
	TextBox(float xPos, float yPos, float xSize, float ySize, string text, sf::Font& font)
	{
		boxSprite.setSize(sf::Vector2f(xSize, ySize));
		boxSprite.setPosition(sf::Vector2f(xPos, yPos));
		boxSprite.setFillColor(sf::Color(110, 110, 110));
		boxSprite.setOutlineColor(sf::Color(10, 10, 10));
		boxSprite.setOutlineThickness(4);

		sf::Color textColor = sf::Color(0, 253, 171);

		boxText.setFont(font);
		boxText.setString("test");
		boxText.setCharacterSize(24);
		boxText.setFillColor(textColor);
		boxText.setPosition(xPos, yPos);
	}
	
	void Draw(sf::RenderWindow& window)
	{
		window.draw(boxSprite);
		window.draw(boxText);
	}

	sf::Rect<float> getGlobalBounds()
	{
		return boxSprite.getGlobalBounds();
	}
};