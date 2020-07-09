#include "Game.h"


void main()
{
	srand(time(NULL));
	Game game;
	while (game.isRunning())
	{

		game.update();

		game.render();
	}

}