#pragma once
#include "Global.h"




class map
{
public:
	map(const int mapSizeX, const int mapSizeY, sf::Window& window);
	~map();

	void render(sf::RenderWindow& window);
	void readWrite(const char* filepath);
	
	unsigned int** mapGrid;

private:
	

	sf::Image mapImage;

	

	
	sf::RectangleShape mapSpr;
	

	const int mapSizeX;
	const int mapSizeY;

	unsigned int cell;
};

