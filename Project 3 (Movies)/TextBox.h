#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class TextBox
{
	sf::RectangleShape boxSprite;
	sf::Text boxText;
	float xPosText;
	float yPosText;
	bool selected;
	int charSize;

public:
	TextBox(float xPos, float yPos, float xSize, float ySize, sf::String& text, sf::Font& font, int charSize)
	{
		this->xPosText = xPos + xSize / 2;
		this->yPosText = yPos + ySize / 4;
		this->charSize = charSize;
		boxSprite.setSize(sf::Vector2f(xSize, ySize));
		boxSprite.setPosition(sf::Vector2f(xPos, yPos));
		boxSprite.setFillColor(sf::Color(110, 110, 110));
		boxSprite.setOutlineColor(sf::Color(15, 15, 15));
		boxSprite.setOutlineThickness(4);

		sf::Color textColor = sf::Color(255, 255, 255);

		boxText.setFont(font);
		boxText.setString(text);
		boxText.setCharacterSize(charSize);
		boxText.setFillColor(textColor);
		boxText.setPosition(xPosText - 6.3 * (text.getSize() - 1), yPosText);
		boxText.setOutlineColor(sf::Color(10, 10, 10));
		boxText.setOutlineThickness(2);
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

	void updateText(sf::String& newText)
	{
		boxText.setString(newText);
		if (newText.getSize() > 30)
		{
			int charSize = 20 - (newText.getSize() - 30) * .4;
			boxText.setCharacterSize(charSize);
			boxText.setPosition(xPosText - 0.31 * charSize * (newText.getSize() - 1), yPosText);
		}
		else
		{
			boxText.setCharacterSize(20);
			boxText.setPosition(sf::Vector2f(xPosText - 6.3 * (newText.getSize() - 1), yPosText));
		}
	}

	bool isSelected()
	{
		return selected;
	}

	void setSelect()
	{
		selected = true;
		boxSprite.setFillColor(sf::Color(130, 130, 130));
	}

	void unselect()
	{
		selected = false;
		boxSprite.setFillColor(sf::Color(110, 110, 110));
	}

	void setTextPos(float x, float y)
	{
		boxText.setPosition(x, y);
	}
};