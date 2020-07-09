#pragma once
#include "Player.h"
#include "Ball.h"

#include "StarBackground.h"

class Game
{
private:
	sf::RenderWindow *window;
	sf::Event SFMLEvent;

	Player *player1;
	Player *player2;
	Ball *ball;

	sf::Font font;
	sf::Text uiTextPlayer;

	StarBackground *background;

	void initFont();
	void initText();
public:
	Game();
	~Game();
	bool isRunning();

	void pollEvents();

	void updateText();
	void updateCollisions();
	void update();
	void render();
};

