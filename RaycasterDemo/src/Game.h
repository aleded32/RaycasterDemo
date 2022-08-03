#pragma once
#include "Global.h"


class Game
{
public:

	Game();
	~Game();
	

	void update();
	void clean();
	void render();
	void eventPoll();

private:

	sf::RenderWindow* window;
	sf::Event e;
	

	//Time time;

	entity* player;

	map* level1Map;
	Raycaster raycaster;
};

