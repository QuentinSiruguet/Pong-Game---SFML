#include "Game.h"



void Game::initFont()
{
	this->font.loadFromFile("Font/LemonMilk.otf");
	
}

void Game::initText()
{
	this->uiTextPlayer.setFont(this->font);
	this->uiTextPlayer.setCharacterSize(30);
	this->uiTextPlayer.setFillColor(sf::Color::White);
}

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Pong", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->player1 = new Player(this->window, sf::Vector2f(100.f, 100.f), 1);
	this->player2 = new Player(this->window, sf::Vector2f(this->window->getSize().x - 100.f, 100.f), 2);
	this->ball = new Ball(this->window);
	this->initFont();
	this->initText();

	this->background = new StarBackground(this->window, 1, 100);
}


Game::~Game()
{
	delete this->player1;
	delete this->player2;
	delete this->ball;
	delete this->background;
	delete this->window;
	
}

bool Game::isRunning()
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->SFMLEvent))
	{
		switch (this->SFMLEvent.type)
		{
		case sf::Event::KeyPressed:
			if (this->SFMLEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Score Player 1 : " << this->player1->getScore() << " \t\t\tZ/S | O/L\t\t\t Score Player 2 : " << this->player2->getScore();
	this->uiTextPlayer.setString(ss.str());

	this->uiTextPlayer.setPosition(this->window->getSize().x / 2 - this->uiTextPlayer.getGlobalBounds().width / 2, 10.f);
}

void Game::updateCollisions()
{
	//Collisions Player Ball
	if (this->ball->getGlobalBounds().intersects(this->player1->getGlobalBounds()) || this->ball->getGlobalBounds().intersects(this->player2->getGlobalBounds()))
		this->ball->changeDirection();

}

void Game::update()
{
	this->background->updateBlink();
	this->background->move(sf::Vector2f(0.f,1.f));
	this->pollEvents();
	this->updateText();
	this->player1->update();
	this->player2->update();
	int resultUpdate = this->ball->update();
	if (resultUpdate == 1)
	{
		this->ball->resetBall();
		this->player1->incrementScore();
	}
	if (resultUpdate == 2)
	{
		this->ball->resetBall();
		this->player2->incrementScore();
	}
	this->updateCollisions();
}

void Game::render()
{
	this->window->clear();

	this->background->render(this->window);
	this->player1->render();
	this->player2->render();
	this->ball->render();

	this->window->draw(this->uiTextPlayer);

	this->window->display();
}
