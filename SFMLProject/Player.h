#pragma once
#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>


class Player
{
private:
	sf::RectangleShape shape;
	sf::RenderWindow *window;
	int playerNumber;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	float speed;
	int score;

	void initVariables(sf::RenderWindow *window, int playerNumber);
	void initShape(sf::Vector2f spawnPos);
public:
	Player(sf::RenderWindow *window, sf::Vector2f spawnPos, int playerNumber);
	~Player();
	sf::FloatRect getGlobalBounds();
	int getScore();

	void incrementScore();

	void updateMovement();
	void update();
	void render();
};

