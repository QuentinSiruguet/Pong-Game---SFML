#include "Player.h"

void Player::initVariables(sf::RenderWindow * window, int playerNumber)
{
	this->window = window;
	this->playerNumber = playerNumber;
	this->speed = 20.f;
	this->score = 0;
	if (this->playerNumber == 1)
	{
		this->upKey = sf::Keyboard::Z;
		this->downKey = sf::Keyboard::S;
		this->shape.setFillColor(sf::Color::Red);
	}
	else if (this->playerNumber == 2)
	{
		this->upKey = sf::Keyboard::O;
		this->downKey = sf::Keyboard::L;
		this->shape.setFillColor(sf::Color::Blue);
	}
}

void Player::initShape(sf::Vector2f spawnPos)
{
	this->shape.setPosition(spawnPos);
	this->shape.setSize(sf::Vector2f(10,this->window->getSize().y/5));
}

Player::Player(sf::RenderWindow * window, sf::Vector2f spawnPos, int playerNumber)
{
	this->initVariables(window,playerNumber);
	this->initShape(spawnPos);
}

Player::~Player()
{

}

sf::FloatRect Player::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

int Player::getScore()
{
	return this->score;
}

void Player::incrementScore()
{
	this->score++;
}

void Player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(this->upKey))
	{
		this->shape.move(sf::Vector2f(0.f, -this->speed));
	}
	if (sf::Keyboard::isKeyPressed(this->downKey))
	{
		this->shape.move(sf::Vector2f(0.f, this->speed));
	}

	if (this->shape.getPosition().y < 0)
		this->shape.setPosition(this->shape.getPosition().x, 0.f);
	else if (this->shape.getPosition().y + this->shape.getSize().y > this->window->getSize().y)
		this->shape.setPosition(this->shape.getPosition().x, this->window->getSize().y - this->shape.getSize().y);
}

void Player::update()
{
	this->updateMovement();
}

void Player::render()
{
	this->window->draw(this->shape);
}
