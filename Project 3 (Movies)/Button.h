#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Button
{
	sf::Sprite buttonSprite;
	string pressImage;
	string unpressImage;
	bool isPressed;
	
public:
	Button(float xPos, float yPos, string pressed, string unpressed)
	{
		buttonSprite.setScale(0.28, 0.28);
		buttonSprite.setPosition(xPos, yPos);
		buttonSprite.setTexture(TextureManager::GetTexture(unpressed));
		pressImage = pressed;
		unpressImage = unpressed;
		isPressed = false;
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(buttonSprite);
	}

	void setPressed()
	{
		isPressed = true;
		buttonSprite.setTexture(TextureManager::GetTexture(pressImage));
	}

	void unPress()
	{
		isPressed = false;
		buttonSprite.setTexture(TextureManager::GetTexture(unpressImage));
	}

	bool checkPressed()
	{
		return isPressed;
	}

	sf::Rect<float> getGlobalBounds()
	{
		return buttonSprite.getGlobalBounds();
	}
};