#include "Platform/Platform.hpp"
#include "classes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
using namespace std;

int main()
{
	//const double PI = 3.1415928;
	vector<Bullet*> bullets;
	vector<Asteroid*> astVec;
	int numOfAsteroids = 10;
	int asteroidsOut = 0;
	sf::RenderWindow window(sf::VideoMode(2500, 2000), "sped game", sf::Style::Default); //default style
	float width = window.getSize().x;
	float height = window.getSize().y;
	sf::Texture bobtex;
	sf::Texture bulTex;
	sf::Texture smallTex;
	sf::Texture mediumTex;
	sf::Texture largeTex;
	srand((unsigned)time(NULL));
	bulTex.loadFromFile("content/ban.png");
	bobtex.loadFromFile("content/min.png");
	smallTex.loadFromFile("content/small_asteroid.png");
	mediumTex.loadFromFile("content/medium_asteroid.png");
	largeTex.loadFromFile("content/large_asteroid.png");
	Bob bob(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), bobtex, 300.0f, 300.0f); //created instance of bob, size 200, placed in the center, and with texture bobtex
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Clock bulletClock;
	sf::Clock minion;

	sf::Texture min0;
	sf::Texture min1;
	sf::Texture min2;
	sf::Texture min3;
	sf::Texture min4;
	sf::Texture min5;
	sf::Texture min6;
	sf::Texture min7;
	sf::Texture min8;
	sf::Texture min9;
	sf::Texture min10;
	sf::Texture min11;
	sf::Texture min12;
	sf::Texture min13;


	min0.loadFromFile("content/minion/min0.png");
	min1.loadFromFile("content/minion/min1.png");
	min2.loadFromFile("content/minion/min2.png");
	min3.loadFromFile("content/minion/min3.png");
	min4.loadFromFile("content/minion/min4.png");
	min5.loadFromFile("content/minion/min5.png");
	min6.loadFromFile("content/minion/min6.png");
	min7.loadFromFile("content/minion/min7.png");
	min8.loadFromFile("content/minion/min8.png");
	min9.loadFromFile("content/minion/min9.png");
	min10.loadFromFile("content/minion/min10.png");
	min11.loadFromFile("content/minion/min11.png");
	min12.loadFromFile("content/minion/min12.png");
	min13.loadFromFile("content/minion/min13.png");
	vector<sf::Texture> min = {min0,min1,min2,min3,min4,min5,min6,min7,min8,min9,min10,min11,min12,min13};

	//window.setFramerateLimit(60);


	int textureIndex = 0;

	while (window.isOpen())

	{
		sf::Event evet;
		while (window.pollEvent(evet))
		{
			switch (evet.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					std::cout << "New window:" << evet.size.width << "," << evet.size.height << std::endl;
					break;

				default:
					// do nothing
					break;
			}
		}
		sf::Time currentTime = clock.getElapsedTime();
		sf::Time deltaTime = currentTime - previousTime; //time elapsed in one frame
		sf::Time bulletTime = bulletClock.getElapsedTime();
		sf::Time minionTime = minion.getElapsedTime();


		previousTime = currentTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			bob.rotate(-deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			bob.rotate(deltaTime.asSeconds());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
		{

			bob.setBoost(true);
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
		{

			bob.setBoost(false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
		{

			bob.setPos();
		}
		bob.update(deltaTime.asSeconds());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && bulletTime.asSeconds() >= .3) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
		{
			bulletClock.restart();
			Bullet* bullet = new Bullet(sf::Vector2f(70.0f, 70.0f), bob.getPosition(), bulTex, 5000.0f, bob.getRotation());
			bullets.push_back(bullet);
		}

		//asteroid handeling
		if (asteroidsOut != numOfAsteroids)
		{
			for (int i = 1; i <= numOfAsteroids; i++)
			{
				float xCord = rand() % 2500;
				float yCord = rand() % 1800;
				//float size = rand() % 3; // will use this as size
				Asteroid* roid = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 300.0f, 3); // will divide speed by size so size proportional
				astVec.push_back(roid);
				asteroidsOut = i;
			}
		}

		window.clear();

		for (auto iter2 = astVec.begin(); iter2 != astVec.end(); ++iter2)
		{
			Asteroid* roid = *iter2;
			bool asteroidDestroyed = false;
			for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
			{

				Bullet* bullet = *iter; //sets bullet = to the object pointed to by ite
				if (bullet->getPosition().x > width || bullet->getPosition().x < 0.0f || bullet->getPosition().y > height || bullet->getPosition().y < 0.0f)
				{
					iter = bullets.erase(iter);
					delete bullet;
					//cout << "bullet" << endl;
					break;
				}

				if (bullet->getPosition().x < roid->getPosition().x + roid->getInt() * 50 && bullet->getPosition().x >= roid->getPosition().x - roid->getInt() * 50 && bullet->getPosition().y < roid->getPosition().y + roid->getInt() * 50 && bullet->getPosition().y >= roid->getPosition().y - roid->getInt() * 50)
				{

					float xCord = roid->getPosition().x;
					float yCord = roid->getPosition().y;

					int sizer = roid->getInt();
					iter = bullets.erase(iter);
					delete bullet;

					iter2 = astVec.erase(iter2); //this line caused crash. WHY BRUH
					delete roid;
					asteroidDestroyed = true;

					if (sizer == 3)
					{
						Asteroid* babyRoid1 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 400.0f, 2); // will divide speed by size so size proportional
						Asteroid* babyRoid2 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 400.0f, 2); // will divide speed by size so size proportional
						astVec.push_back(babyRoid1);
						astVec.push_back(babyRoid2);
					}
					if (sizer == 2)
					{
						Asteroid* babyRoid1 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 700.0f, 1); // will divide speed by size so size proportional
						Asteroid* babyRoid2 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 700.0f, 1); // will divide speed by size so size proportional
						astVec.push_back(babyRoid1);
						astVec.push_back(babyRoid2);
					}

					break;

					//break;
				}
			}
			if (asteroidDestroyed)
			{
				if (iter2 == astVec.end())
				{
					break;
				}
				else
				{
					--iter2;
				}
			}
		}
		for (auto iter = astVec.begin(); iter != astVec.end(); ++iter) //range based for loop that runs through array of bullets
		{
			Asteroid* roid = *iter;
			roid->update(deltaTime.asSeconds(), window);
		}

		for (auto& bullet : bullets)
		{
			bullet->draw(window);
			bullet->move(deltaTime.asSeconds());
		}
		if(minionTime.asSeconds() > .5f){
			textureIndex++;

		if(textureIndex < 14){
			bob.setTexture(min[textureIndex]);
		}
		}
		bob.draw(window);

		window.display();


	}
	return 0;
}
