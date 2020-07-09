#ifndef STARBACKGROUND_H
#define STARBACKGROUND_H

#include <SFML\Graphics.hpp>



class StarBackground
{
private:

	class Star {
	private:
		sf::RenderTarget *target;
		sf::CircleShape star;

		float blinkSpeedMax;
		float blinkSpeed;

		float movementSpeed = rand() % 1 + 2;

		int alphaMin = rand() % 95 + 25;
		int alphaMax = rand() % 120 + 120;
		int alpha = rand() % this->alphaMax;
		int alphaWay = rand() % 2 + 1;

		int colorWay = rand() % 100 + 1;
		int colorR = 255;
		int colorG = 255;
		int colorB = 255;

	public:
		Star(sf::RenderTarget *target, int speed) {
			this->target = target;

			//Blink speed
			this->blinkSpeedMax = static_cast<float>(rand() % speed + speed);
			this->blinkSpeed = this->blinkSpeedMax;

			//Star things
			this->star.setRadius(this->movementSpeed); //Radius depend of the moveSpeed
			this->star.setPosition(this->target->mapPixelToCoords(sf::Vector2i(rand() % this->target->getSize().x, rand() % this->target->getSize().y), this->target->getView()));

			//Star color : 90% White, 5% Red, 3%Blue, 1% Green, 1%Purple
			//Blue
			if (this->colorWay > 90 && this->colorWay < 95) 
			{
				this->colorR = 40;
				this->colorG = 40;
				this->colorB = 255;
			}
			//Red
			else if (this->colorWay > 95 && this->colorWay < 99) 
			{
				this->colorR = 255;
				this->colorG = 120;
				this->colorB = 120;
			}
			//Green
			else if (this->colorWay == 99) 
			{
				this->colorR = 120;
				this->colorG = 255;
				this->colorB = 120;
			}
			//Purple
			else if (this->colorWay == 100) 
			{
				this->colorR = 120;
				this->colorG = 0;
				this->colorB = 255;
			}
			this->star.setFillColor(sf::Color(this->colorR, this->colorG, this->colorB, this->alpha));
		}
		//Move star
		void move(sf::Vector2f move) 
		{
			this->star.move(move*this->movementSpeed);
			if (this->star.getPosition().x < this->target->mapPixelToCoords(sf::Vector2i(0, 0), this->target->getView()).x) //Left
				this->star.setPosition(this->target->mapPixelToCoords(sf::Vector2i(this->target->getSize().x, rand() % this->target->getSize().y), this->target->getView()));

			if (this->star.getPosition().y < this->target->mapPixelToCoords(sf::Vector2i(0, 0), this->target->getView()).y) //Top
				this->star.setPosition(this->target->mapPixelToCoords(sf::Vector2i(rand() % this->target->getSize().x, this->target->getSize().y), this->target->getView()));

			if (this->star.getPosition().x > this->target->mapPixelToCoords(sf::Vector2i(this->target->getSize().x, this->target->getSize().y), this->target->getView()).x) //Right
				this->star.setPosition(this->target->mapPixelToCoords(sf::Vector2i(0, rand() % this->target->getSize().y), this->target->getView()));

			if (this->star.getPosition().y > this->target->mapPixelToCoords(sf::Vector2i(this->target->getSize().x, this->target->getSize().y), this->target->getView()).y) //Bottom
				this->star.setPosition(this->target->mapPixelToCoords(sf::Vector2i(rand() % this->target->getSize().x, 0), this->target->getView()));
		}
		//Update Alpha for blink
		void update() 
		{
			if (this->blinkSpeed >= this->blinkSpeedMax)
			{
				if (this->alphaWay == 1)
				{
					if (alpha < alphaMax)
						alpha += rand() % 2 + 1;
					else if (alpha >= alphaMax)
					{
						alphaWay = 2;
						this->alphaMax = rand() % 120 + 120;
					}

				}
				else if (this->alphaWay == 2)
				{
					if (alpha > alphaMin)
						alpha -= rand() % 2 + 1;
					else if (alpha <= alphaMin)
					{
						alphaWay = 1;
						this->alphaMin = rand() % 70 + 50;
					}
				}
				this->star.setFillColor(sf::Color(this->colorR, this->colorG, this->colorB, this->alpha));
				this->blinkSpeed = 0;
			}
			else this->blinkSpeed++;
		}
		//Render star
		void render(sf::RenderTarget *target) {
			target->draw(this->star);
		}
	};

	std::vector <Star> stars;

public:
	StarBackground(sf::RenderTarget *target, int blinkSpeed, int starNumber) {
		for (int i = 0; i < starNumber; i++)
		{
			Star star(target, blinkSpeed);
			this->stars.push_back(star);
		}
	}
	//For each star, move it
	void move(sf::Vector2f move)
	{
		for (auto &star : this->stars)
			star.move(move);
	}
	//For each star, blink it
	void updateBlink() {
		for (auto &star : this->stars)
			star.update();
	}
	//For each star, render it
	void render(sf::RenderTarget *target) {
		for (auto &star : this->stars)
			star.render(target);
	}
};

#endif
