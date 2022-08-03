#include "raycaster.h"
#include <cmath>

Raycaster::Raycaster() :
	brigthness(0)
{
	
	

	floor.setPosition(0, 360);
	floor.setSize(sf::Vector2f(1280, 360));
	floor.setFillColor(sf::Color(90, 44, 212, 255));
	
	


	if(!wallTex.loadFromFile("assets/wall.png"));

	

}

Raycaster::~Raycaster()
{
}

void Raycaster::update(unsigned int** mapGrid, int pPosX, int pPosY, float playerAngle)
{
	performDDA(mapGrid, pPosX, pPosY, playerAngle);
}

void Raycaster::render(sf::RenderWindow & window)
{
	
	window.draw(floor);
	for (Ray r : ray)
	{
		//window.draw(r.wall);
		//window.draw(r.rayline, 2, sf::Lines);
		window.draw(r.line);
		//window.draw(r.raylineVert, 2, sf::Lines);
	}

	

	
}

void Raycaster::performDDA(unsigned int ** mapGrid, int pPosX, int pPosY, float playerAngle)
{

	distT = 0;
	for(int i = 0; i < 45; i++)
	{
		ray[i].angle = playerAngle - (DEGRAD * (i+1));

		if (ray[i].angle > 2 * PI)
			ray[i].angle -= (2 * PI);

		if (ray[i].angle < 0)
			ray[i].angle += (2 * PI);
	}
	
		
	
	for (int r = 0; r < 45; r++) 
	{
		//vertical check
		depthOfField = 0;
		float nTan = -tan(ray[r].angle);

		float disV = 1000000;
		ray[r].vertX = pPosX;
		ray[r].vertY = pPosY;

		//looking right
		if (ray[r].angle > PI2 && ray[r].angle < PI3)
		{

			ray[r].posX = 20 * std::round(pPosX / 20) - 0.0001;
			ray[r].posY = (pPosX - ray[r].posX) * nTan + pPosY;
			ray[r].xOffset = -20;
			ray[r].yOffset = -ray[r].xOffset * nTan;
		}
		//looking left
		else if (ray[r].angle > PI3 || ray[r].angle < PI2)
		{
			ray[r].posX = (20 * std::round(pPosX / 20)) + 20;
			ray[r].posY = (pPosX - ray[r].posX) * nTan + pPosY;
			ray[r].xOffset = 20;
			ray[r].yOffset = -ray[r].xOffset * nTan;
		}
		else if (ray[r].angle == 0 || ray[r].angle == PI)
		{
			ray[r].posX = pPosX;
			ray[r].posY = pPosY;
			depthOfField = DOF;
		}





		searchForHit(depthOfField, ray[r].posX, ray[r].posY, r, pPosX, pPosY, mapGrid, ray[r].vertX, ray[r].vertY, disV);


		depthOfField = 0;
		float coTan = -1/tan(ray[r].angle);

		float disH = 1000000;
		ray[r].horzX = pPosX;
		ray[r].horzY = pPosY;
		
		
		
		//horizontal check
		//looking up
		if (ray[r].angle > PI) 
		{
			
			ray[r].posY = (20 * std::round(pPosY / 20)) - 0.0001;
			ray[r].posX = (pPosY - ray[r].posY) * coTan + pPosX;
			ray[r].yOffset = -20;
			
			ray[r].xOffset = -ray[r].yOffset * coTan;
			
			
		}
		//looking down
		else if (ray[r].angle < PI)
		{
			ray[r].posY = (20 * std::round(pPosY / 20)) + 20;
			ray[r].posX = (pPosY - ray[r].posY) * coTan + pPosX;
			ray[r].yOffset = 20;
			ray[r].xOffset = -ray[r].yOffset * coTan;
			
		}
		else if(ray[r].angle == 0 || ray[r].angle == PI)
		{
			ray[r].posX = pPosX;
			ray[r].posY = pPosY;
			depthOfField = DOF;
		}


		searchForHit(depthOfField, ray[r].posX, ray[r].posY, r, pPosX, pPosY, mapGrid, ray[r].horzX, ray[r].horzY, disH);
		

		

		
		ray[r].wall.setTexture(wallTex);
		

		if (disH < disV) 
		{
			
			ray[r].posX = ray[r].horzX;
			ray[r].posY = ray[r].horzY;
			distT = disH;

			
			//ray[r].wall.setTextureRect(sf::IntRect(std::round(ray[r].posX) - (ray[r].mapX * 20), 0, 1, 20));
			ray[r].line.setFillColor(sf::Color(140, 0, 0, 255));
			
			
		}
		else if (disV < disH)
		{
			ray[r].posX = ray[r].vertX;
			ray[r].posY = ray[r].vertY;
			distT = disV;

			
			//ray[r].wall.setTextureRect(sf::IntRect((ray[r].mapY * 20) - std::round(ray[r].posY), 0, 1, 20));
			//std::cout << std::round(ray[r].posY) - (ray[r].mapY * 20) << std::endl;
			ray[r].line.setFillColor(sf::Color(180, 0, 0, 255));
			
		}

		
		
		//draw 3D space

		float fixAngle = playerAngle - ray[r].angle;
		if (fixAngle < 0)
			fixAngle += 2 * PI;
		else if (fixAngle > 2 * PI)
			fixAngle -= 2 * PI;


		distT *= cos(fixAngle);


	
		

		lineHeight =  (20 * 720) / distT;
		if (lineHeight > 720)
			lineHeight = 720;

		lineOffset = 360 - (lineHeight >> 1);
		
	

	
		//ray[r].wall.setScale(30, ((lineHeight + lineOffset) - lineOffset)/(float)20);
		//ray[r].wall.setPosition(r* 30, lineOffset);

		

		ray[r].line.setPosition(sf::Vector2f(r * 36, lineOffset));
		ray[r].line.setSize(sf::Vector2f(36,  (lineHeight + lineOffset) - lineOffset));

	
		
	
		
		//ray[r].rayline[0].position = sf::Vector2f(pPosX, pPosY);
		//ray[r].rayline[1].position = sf::Vector2f(ray[r].posX, ray[r].posY);
		//ray[r].rayline->color = sf::Color::Green;

		//ray[r].raylineVert[0].position = sf::Vector2f(pPosX, pPosY);
		//ray[r].raylineVert[1].position = sf::Vector2f(ray[r].vertX, ray[r].vertY);
		//ray[r].raylineVert->color = sf::Color::Red;
		
		

		
	}


	



	


	
	
}
