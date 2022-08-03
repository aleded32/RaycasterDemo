#include "Game.h"

Game::Game()
{


	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "RaycasterDemo");

    player = new entity(90, 90);
	level1Map = new map(64,36, *window);

	level1Map->readWrite("assets/map.png");

	sf::Mouse::setPosition(sf::Vector2i((window->getSize().x/2), (window->getSize().y/2)), *window);

}

Game::~Game()
{
	delete window;
	delete player;
	delete level1Map;
}

void Game::render()
{
	window->clear(sf::Color(100, 0, 0, 255));
	
    
	level1Map->render(*window);
	player->render(*window);
	raycaster.render(*window);

	window->display();
    
}

void Game::eventPoll()
{

	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window->close();
	}


    player->eventHandle();
        
   
   
}

void Game::update()
{
    while (window->isOpen())
    {
		window->setFramerateLimit(60);
       // time.ticks();
        eventPoll();

		
        player->update(*window, level1Map->mapGrid);
		raycaster.update(level1Map->mapGrid, player->getPlayerPos().x, player->getPlayerPos().y, player->getAngle());
        render();
    }
}

void Game::clean()
{
   
}
