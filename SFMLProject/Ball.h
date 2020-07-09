#pragma once
#include <math.h>
#include <iostream>
#include <sstream>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
class Ball
{
private:
	sf::CircleShape shape;
	sf::RenderWindow *window;
	sf::Vector2f direction;
	float speed;
	float resetTimer;
	float resetTimerMax;

	float changeDirectionTimer;
	float changeDirectionTimerMax;

	void initVariables(sf::RenderWindow *window);
	void initShape();
public:
	Ball(sf::RenderWindow *window);
	~Ball();
	sf::FloatRect getGlobalBounds();

	void changeDirection();
	void resetBall();

	int update();
	void render();
};

