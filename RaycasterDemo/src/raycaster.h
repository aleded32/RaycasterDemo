#pragma once
#include "Global.h"


struct Ray 
{
	int hit = 0;
	float posX = 0, posY = 0;
	float angle = 0;
	float vertX = 0, vertY = 0;
	float horzX = 0, horzY = 0;
	float xOffset = 0, yOffset = 0;
	int mapX = 0, mapY =0;
	sf::RectangleShape line;
	sf::Vertex rayline[2];
	sf::Vertex raylineVert[2];
	sf::Sprite wall;
};

class Raycaster 
{
public:

	Ray ray[90];
	
	sf::RectangleShape floor;
	

	Raycaster();
	~Raycaster();

	void update(unsigned int** mapGrid, int pPosX, int pPosY, float playerAngle);
	void render(sf::RenderWindow& window);

private:

	void performDDA(unsigned int** mapGrid, int pPosX, int pPosY, float playerAngle);
	
	sf::Texture wallTex;


	int depthOfField;
	float distT;
	float disV;
	int mapPos;

	float brigthness;


	int lineHeight, lineOffset;

	float getDist(float x1, float x2, float y1, float y2) 
	{
		return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
	}


	void searchForHit(int &depthOfField, float &rPosX, float &rPosY, int &r, int &pPosX, int &pPosY, unsigned int** mapGrid, float &horVerX, float &horVerY, float &dis) 
	{
		if (depthOfField < 40)
		{
			if (ray[r].posX >= 1280)
				ray[r].posX = 1280;
			else if (ray[r].posX <= 0)
				ray[r].posX = 0;

			if (ray[r].posY >= 720)
				ray[r].posY = 720;
			else if (ray[r].posY <= 0)
				ray[r].posY = 0;



			ray[r].mapX = (int)ray[r].posX / 20;
			ray[r].mapY = (int)ray[r].posY / 20;

			mapPos = ray[r].mapY * 64 + ray[r].mapX;

			if (mapPos < (64 * 36) && mapPos > 0 && mapGrid[ray[r].mapY][ray[r].mapX] == 1)
			{

				horVerX = ray[r].posX;
				horVerY = ray[r].posY;

				dis = getDist(pPosX, horVerX, pPosY, horVerY);
				depthOfField = 40;
			}
			else
			{

				searchForHit(depthOfField += 1, ray[r].posX += ray[r].xOffset, ray[r].posY += ray[r].yOffset, r, pPosX, pPosY, mapGrid, horVerX, horVerY, dis);

			}
		}
	}

};