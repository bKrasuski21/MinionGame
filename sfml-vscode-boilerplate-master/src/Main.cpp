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
	bool start = false;
	vector<Asteroid*> astVec;
	int numOfAsteroids = 10;
	int asteroidsOut = 0;
	sf::RenderWindow window(sf::VideoMode(2500, 2000), "sped game", sf::Style::Default); //default style
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
	//Asteroid nigga(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), smallTex, mediumTex, largeTex, 300.0f, 3);
	sf::Clock clock; //do I wanna make a 'new' object in memory for bob, or just bullet?
	sf::Time previousTime = clock.getElapsedTime();
	sf::Clock bulletClock;
	//float decay = 5;
	//float topSpeed = 5;
	//float tempSpeed = 0;
	//window.setFramerateLimit(60);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){
			start = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && bulletTime.asSeconds() >= .3) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
		{
			bulletClock.restart();
			Bullet* bullet = new Bullet(sf::Vector2f(70.0f, 70.0f), bob.getPosition(), bulTex, 5000.0f, bob.getRotation());
			bullets.push_back(bullet);
		}
		for (auto iter = bullets.begin(); iter != bullets.end(); ++iter) //range based for loop that runs through array of bullets
		{
			Bullet* bullet = *iter; //sets bullet = to the object pointed to by iter
			if (bullet->getPosition().x > 2500.0f)
			{
				iter = bullets.erase(iter); // erases current iter, and replaces new iter with the next element
				delete bullet;
				break;
			}
			if (bullet->getPosition().x < 0.0f)
			{

				iter = bullets.erase(iter);
				delete bullet;
				break;
			}
			if (bullet->getPosition().y > 1500.0f)
			{

				iter = bullets.erase(iter);
				delete bullet;
				break;
			}

			if (bullet->getPosition().y < 0.0f)
			{
				iter = bullets.erase(iter);
				delete bullet;
				break;

		}
		}
		//asteroid handeling
		if (start){
		if (asteroidsOut != numOfAsteroids)
		{
			for (int i = 1; i <= numOfAsteroids; i++)
			{
					float xCord = rand() % 2500;
					float yCord = rand() % 1800;
					//float size = rand() % 3; // will use this as size
				Asteroid* roid = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 75.0f, 3); // will divide speed by size so size proportional
				astVec.push_back(roid);
				asteroidsOut = i;
			}
		}
		}
		window.clear();

		for(unsigned long i =0; i < astVec.size(); i++){
			for(auto iter = bullets.begin(); iter != bullets.end(); ++iter){
				Bullet* bullet = *iter; //sets bullet = to the object pointed to by ite
			if(bullet->getPosition().x < astVec[i]->getPosition().x+35 && bullet->getPosition().x >=  astVec[i]->getPosition().x -35){
				//cout << "apple" << endl;
				if (bullet->getPosition().y < astVec[i]->getPosition().y+35 && bullet->getPosition().y >=  astVec[i]->getPosition().y -35){
									cout << "pei" << endl;

				//iter = bullets.erase(iter);
				//delete bullet;

				delete astVec[i];
					}
					break;
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

		bob.draw(window);
		//nigga.draw(window);
		window.display();

		//the black , unclear is white
		//sf::Vector2f pos;
		//pos = bob.getPosition();
		//std::cout << "position of bob=     " << pos.x << "," << pos.y << std::endl;
	}
	return 0;
}
