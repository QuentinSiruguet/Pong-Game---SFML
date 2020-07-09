#include "Ball.h"


void Ball::initVariables(sf::RenderWindow * window)
{
	this->window = window;
	this->speed = 10.f;
	do
	{
		this->direction.x = rand() % 3 - 1;
		this->direction.y = rand() % 3 - 1;
	} while (this->direction.x == 0 || this->direction.y == 0);

	this->resetTimerMax = 120.f;
	this->resetTimer = 0.f;

	this->changeDirectionTimerMax = 60.f;
	this->changeDirectionTimer = this->changeDirectionTimerMax;
}

void Ball::initShape()
{
	this->shape.setRadius(10.f);
	this->shape.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
}

Ball::Ball(sf::RenderWindow * window)
{
	this->initVariables(window);
	this->initShape();
}

Ball::~Ball()
{

}

sf::FloatRect Ball::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}

void Ball::changeDirection()
{
	if (this->changeDirectionTimer >= this->changeDirectionTimerMax)
	{
		this->direction.x *= -1;
		this->changeDirectionTimer = 0.f;
	}
}

void Ball::resetBall()
{
	this->shape.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	do
	{
		this->direction.x = rand() % 3 - 1;
		this->direction.y = rand() % 3 - 1;
	} while (this->direction.x == 0 || this->direction.y == 0);
	this->resetTimer = 0;
}

int Ball::update()
{
	if (this->changeDirectionTimer < this->changeDirectionTimerMax)
		this->changeDirectionTimer++;
	int playerWin = 0;
	if (this->resetTimer < this->resetTimerMax)
		this->resetTimer++;
	if (this->resetTimer >= this->resetTimerMax)
	{
		this->shape.move(this->direction*speed);
		if (this->shape.getPosition().y < 0)
		{
			this->direction.y *= -1;
			this->shape.setPosition(this->shape.getPosition().x, 0.f);
		}
		else if (this->shape.getPosition().y + this->shape.getRadius() > this->window->getSize().y)
		{
			this->direction.y *= -1;
			this->shape.setPosition(this->shape.getPosition().x, this->window->getSize().y - this->shape.getRadius());
		}

		if (this->shape.getPosition().x < 0)
			playerWin = 2;
		else if (this->shape.getPosition().x > this->window->getSize().x)
			playerWin = 1;
	}
	return playerWin;

}

void Ball::render()
{
	this->window->draw(this->shape);
}
