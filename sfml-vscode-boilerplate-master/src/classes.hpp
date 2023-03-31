#pragma once

#include <SFML/Graphics.hpp>

class Bob
{
public:
	Bob(sf::Vector2f size, sf::Vector2f position, sf::Texture& texture, float rotVel, float movVel);

	float getRotation() const;
	float getRotVel() const;
	float getMovVel() const;
	sf::Vector2f getPosition() const;
	void move(float x, float y);
	void rotate(float time);
	void draw(sf::RenderWindow& window);
	void update(float time);
	void setBoost(bool truth);
	void setPos();

private:
	sf::RectangleShape m_shape;
	float m_rotVel;
	float m_movVel;
	sf::Vector2f velocity;
	bool boosting;
	float x;
	float y;
	float dx;
	float dy;
};

class Bullet
{
public:
	Bullet(sf::Vector2f size, sf::Vector2f position, sf::Texture& texture, float movVel, float bRot);

	float getRotation() const;
	float getMovVel() const;
	sf::Vector2f getPosition() const;
	void move(float time);
	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape m_shape;
	float m_movVel;
};

class Asteroid
{
public:
	Asteroid(sf::Vector2f position, sf::Texture& smallTex, sf::Texture& mediumTex, sf::Texture& largeTex, float movVel, int asteroidSize);
	float getSize() {return asteroidSize;};
	float getMovVel() const;
	sf::Vector2f getPosition() const;
	void move(float time);
	void setRotation();
	void draw(sf::RenderWindow& window);
	void update(float time, sf::RenderWindow& window);

private:
	sf::RectangleShape m_shape;
	float m_movVel;
	int asteroidSize;
	sf::Texture small;
	sf::Texture medium;
	sf::Texture large;
};