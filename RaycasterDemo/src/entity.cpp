#include "entity.h"

entity::entity(int startPosX, int startPosY)
	:posX(startPosX), posY(startPosY), speed(0), mouseSentivity(0.1),
	 angle(0), oldMouseX(0), oldMouseY(0), yaw(0), deltaX(0.1), deltaY(0),
	yOffset(0), xOffset(0)
{

	loadSprite("assets/player.png");

	sprite.setPosition(startPosX, startPosY);
	
	sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));

	speed = 3;

	
}

entity::~entity()
{
}

void entity::update(sf::RenderWindow& window, unsigned int** mapGrid)
{

	

	switch (currentDirection)
	{
		case entity::direction::none:
			break;
		case entity::direction::north:
			collisionUp(mapGrid);
			break;
		case entity::direction::east:
			angle += 0.02;
			if (angle > 2 * PI)
				angle -= (2 * PI);

			deltaX = cos(angle) * 2;
			deltaY = sin(angle) * 2;
			break;
		case entity::direction::south:
			collisionDown(mapGrid);
			break;
		case entity::direction::west:
			angle -= 0.02;
			if (angle < 0)
				angle += (2 * PI);

			deltaX = cos(angle) * 2;
			deltaY = sin(angle) * 2;
			break;
	}
		
	sprite.setRotation(angle * (180 / 3.141));

	sprite.setPosition(posX, posY);
	
}

void entity::render(sf::RenderWindow& window) 
{
	//window.draw(sprite);
}



void entity::eventHandle()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		currentDirection = direction::north;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		currentDirection = direction::east;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		currentDirection = direction::west;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		currentDirection = direction::south;
	}
	else
	{
		currentDirection = direction::none;
	}
		
	

	
}





void entity::collisionUp(unsigned int** mapGrid)
{
	if (deltaX < 0)
		xOffset = -1;
	else
		xOffset = 1;

	if (deltaY < 0)
		yOffset = -1;
	else
		yOffset = 1;

	int mapX = posX / 20;
	int mapY = posY / 20;


	
		if (mapGrid[mapY][mapX + xOffset] == 0) 
		{
			posX += deltaX;
		}
		if (mapGrid[mapY + yOffset][mapX] == 0)
		{
			posY += deltaY;
		}
	

}

void entity::collisionDown(unsigned int** mapGrid)
{
	if (deltaX < 0)
		xOffset = -1;
	else
		xOffset = 1;

	if (deltaY < 0)
		yOffset = -1;
	else
		yOffset = 1;

	int mapX = posX / 20;
	int mapY = posY / 20;



	if (mapGrid[mapY][mapX - xOffset] == 0)
	{
		posX -= deltaX;
	}
	if (mapGrid[mapY - yOffset][mapX] == 0)
	{
		posY -= deltaY;
	}


}

