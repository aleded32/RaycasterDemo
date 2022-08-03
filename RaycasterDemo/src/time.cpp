/*#include "time.h"


Time::Time()
    : FPS(60), frameDelay(1000/60), lastFrameTime(0), targetFrameTime(1.5f), deltaTime(0), frametime(0), framestart(0)
{
}

Time::~Time()
{
}

void Time::ticks()
{

	framestart = SDL_GetTicks();

	frametime = SDL_GetTicks() - framestart;

	if (frameDelay > frametime)
	{
		SDL_Delay(frameDelay - frametime);
	}
	

   

}

void Time::deltaTimefunc()
{
	deltaTime = (SDL_GetTicks() - lastFrameTime) * (FPS/1000);

	if (deltaTime > targetFrameTime)
		deltaTime = targetFrameTime;

	lastFrameTime = SDL_GetTicks();
}*/
