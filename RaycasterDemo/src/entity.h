#pragma once
#include "Global.h"

class entity
{
public:

	entity(int startPosX, int startPosY);
	~entity();

	void update(sf::RenderWindow& window, unsigned int** mapGrid);
	void render(sf::RenderWindow& window);
	
	void eventHandle();

	sf::Vector2f getPlayerPos() 
	{
		return sf::Vector2f(posX, posY);
	}

	float getAngle() 
	{
		return angle;
	}

private:

	float posX;
	float posY;

	int speed;
	float angle;

	int xOffset, yOffset;
	
	int oldMouseX, oldMouseY;

	int deltaX, deltaY;

	float mouseSentivity;
	float yaw;
	float pitch;

	float rotX, rotY;
	float dir;

	enum class direction {none, north, west, south , east};
	direction currentDirection;

	sf::Sprite sprite;
	sf::Texture tex;

	void collisionUp(unsigned int** mapGrid);
	void collisionDown(unsigned int** mapGrid);


	void loadSprite(const char* filepath) 
	{
		
		if (tex.loadFromFile(filepath)); 
		
		sprite.setTexture(tex);

		
		
	}
	

};

