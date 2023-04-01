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
	int numOfAsteroids = 5;
	int asteroidsOut = 0;
	sf::RenderWindow window(sf::VideoMode(2500, 2000), "sped game", sf::Style::Default); //default style
	float width = window.getSize().x;
	float height = window.getSize().y;
	sf::Texture bobtex;
	sf::Texture bulTex;
	sf::Texture smallTex; //test comment
	sf::Texture mediumTex;
	sf::Texture largeTex;
	sf::Texture damageTex;
	srand((unsigned)time(NULL));
	bulTex.loadFromFile("content/ban.png");
	bobtex.loadFromFile("content/minion/cum0.png");
	smallTex.loadFromFile("content/small_asteroid.png");
	mediumTex.loadFromFile("content/medium_asteroid.png");
	largeTex.loadFromFile("content/large_asteroid.png");
	damageTex.loadFromFile("content/minion/pink.png");
	Bob bob(sf::Vector2f(250.0f, 250.0f), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), bobtex, 300.0f, 300.0f); //created instance of bob, size 200, placed in the center, and with texture bobtex
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Clock bulletClock;
	sf::Clock minion;
	sf::Clock bounce;
	vector<sf::Texture> min; //change

	for (int i = 0; i < 55; i++)
	{
		string filename = "content/minion/cum" + to_string(i) + ".png";
		sf::Texture minion;
		minion.loadFromFile(filename);
		min.push_back(minion);
	}

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
		sf::Time bounceTime = bounce.getElapsedTime();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && bulletTime.asSeconds() >= 0.001) //FEATURES TO ADD: ACCELERATION/DECELLERATION????
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

				//float size = rand() % 4; // will use this as size
				//cout << size << endl;
				Asteroid* roid = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 800.0f, 3); // will divide speed by size so size proportional
				astVec.push_back(roid);

				asteroidsOut = i;
			}
		}

		window.clear();
		int i = 0;
		bool beenhit = true;
		for (auto iter2 = astVec.begin(); iter2 != astVec.end(); iter2++)
		{
			Asteroid* roid = *iter2;
			for (auto iter3 = astVec.begin(); iter3 != astVec.end(); ++iter3)
			{
				Asteroid* tempRoid = *iter3;

				if (*iter2 != *iter3)
				{
					//cout << roid->getPosition().x << " " << roid->getPosition().y << endl;
					if (bounceTime.asSeconds() > 0.5 && beenhit && roid->getPosition().x + (28 * roid->getSize()) >= tempRoid->getPosition().x - (tempRoid->getSize() * 28) && roid->getPosition().x - (28 * roid->getSize()) <= tempRoid->getPosition().x + (tempRoid->getSize() * 28) && (roid->getPosition().y + (28 * roid->getSize()) >= tempRoid->getPosition().y - (tempRoid->getSize() * 28) && roid->getPosition().y - (28 * roid->getSize()) <= tempRoid->getPosition().y + (tempRoid->getSize() * 28)))
					{
						beenhit = false;
						//float temp = tempRoid->getCurRotation();
						float temp = rand() % 1000;
						tempRoid->setNewRotation(temp);
						i++;
						cout << "apple" << i << endl;
						temp = rand() % 1000;
						roid->setNewRotation(temp);

						bounce.restart();
						break;
					}
				}
			}
		}

		for (auto iter2 = astVec.begin(); iter2 != astVec.end(); ++iter2)
		{
			Asteroid* roid = *iter2;
			bool asteroidDestroyed = false;
			if (roid != nullptr)
			{
				for (auto iter = bullets.begin(); iter != bullets.end(); ++iter)
				{
					Bullet* bullet = *iter; //sets bullet = to the object pointed to by ite
					if (bullet == nullptr)
					{
						cout << "what" << endl;
					}
					if (roid == nullptr)
					{
						cout << "rpid " << endl;
					}
					if (bullet != nullptr && roid != nullptr)
					{
						if (bullet->getPosition().x > width || bullet->getPosition().x < 0.0f || bullet->getPosition().y > height || bullet->getPosition().y < 0.0f)
						{
							cout << "step 1" << endl;
							iter = bullets.erase(iter);
							delete bullet;
							//cout << "bullet" << endl;
							break;
						}
						//if (bob.getPosition().x * 125 < roid->getPosition().x + roid->getInt() * 50 && bob.getPosition().x >= roid->getPosition().x - roid->getInt() * 50 && bob.getPosition().y < roid->getPosition().y + roid->getInt() * 50 && bob.getPosition().y >= roid->getPosition().y - roid->getInt() * 50){
						//	cout << "bob hit" << endl;
						//}
						if (bullet->getPosition().x < roid->getPosition().x + (roid->getSize() * 50) && bullet->getPosition().x >= roid->getPosition().x - (roid->getSize() * 50) && bullet->getPosition().y < roid->getPosition().y + (roid->getSize() * 50) && bullet->getPosition().y >= roid->getPosition().y - (roid->getSize() * 50))
						{
							cout << "step 3" << endl;
							float xCord = roid->getPosition().x;
							float yCord = roid->getPosition().y;
							int sizer = roid->getSize();

							if (bullet != nullptr)
							{
								cout << "step 4 " << endl;
								iter = bullets.erase(iter);
								delete bullet;
							}

							if (roid != nullptr)
							{
								///int step = 0;
								cout << "step 5" << endl;
								iter2 = astVec.erase(iter2);
								cout << "after step 5" << endl;
								delete roid;
								asteroidDestroyed = true;

								if (sizer == 3)
								{
									cout << "step 6 " << endl;
									Asteroid* babyRoid1 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 400.0f, 2); // will divide speed by size so size proportional
									Asteroid* babyRoid2 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 400.0f, 2); // will divide speed by size so size proportional
									astVec.push_back(babyRoid1);
									astVec.push_back(babyRoid2);
								}
								if (sizer == 2)
								{
									cout << "step 7 " << endl;
									Asteroid* babyRoid1 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 700.0f, 1); // will divide speed by size so size proportional
									Asteroid* babyRoid2 = new Asteroid(sf::Vector2f(xCord, yCord), smallTex, mediumTex, largeTex, 700.0f, 1); // will divide speed by size so size proportional
									astVec.push_back(babyRoid1);
									astVec.push_back(babyRoid2);
								}
							}

							break;

							//break;
						}
					}
				}
			}

			if (asteroidDestroyed)
			{
				cout << "step 8" << endl;
				if (iter2 == astVec.end())
				{
					cout << "step 9" << endl;
					break;
				}
				else
				{
					cout << "step 10" << endl;
					--iter2;
					cout << "after step 10" << endl;
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

		if (minionTime.asSeconds() > .1f)
		{
			textureIndex++;

			if (textureIndex < 55)
			{
				bob.setTexture(min[textureIndex]);
				minion.restart();
			}
			else
			{
				textureIndex = 0;
			}
		}

		bob.draw(window);

		window.display();
	}
	return 0;
}
