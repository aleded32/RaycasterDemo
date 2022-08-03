#include "map.h"

map::map(const int mapSizeX, const int mapSizeY, sf::Window& window) :
	mapSizeX(mapSizeX), mapSizeY(mapSizeY)
{
	mapSpr.setSize(sf::Vector2f(20,20));
	mapSpr.setPosition(0, 0);
	mapSpr.setOutlineThickness(1.0f);
	mapSpr.setOutlineColor(sf::Color::White);
	
	
}

map::~map() 
{
	delete mapGrid;
}

void map::readWrite(const char* filepath) 
{
	
	if (mapImage.loadFromFile(filepath));

	mapGrid = new unsigned int*[mapSizeY];
	
	for (int i = 0; i < mapSizeY; i++) 
	{
		mapGrid[i] = new unsigned int[mapSizeX];

		for (int j = 0; j < mapSizeX; j++) 
		{
			
			if (mapImage.getPixel(j, i) == sf::Color::Black)
				cell = 0;
			else if (mapImage.getPixel(j, i) == sf::Color(0,0,170,255)) 
				cell = 1;
				

			
			mapGrid[i][j] = cell;

			
		}
		
	}

	

}

void map::render(sf::RenderWindow& window)
{
	/*for (int i = 0; i < mapSizeY; i++)
	{

		for (int j = 0; j < mapSizeX; j++)
		{
			

			if (mapGrid[i][j] == 0)
				mapSpr.setFillColor(sf::Color::Black);
			else if(mapGrid[i][j] == 1)
				mapSpr.setFillColor(sf::Color::Blue);

			

			mapSpr.setPosition(20 * j, 20 * i);
			window.draw(mapSpr);
		}

		
	}*/
}