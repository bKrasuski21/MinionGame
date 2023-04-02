#include "classes.hpp"
#include <cmath>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <iostream>

Bob::Bob(sf::Vector2f size, sf::Vector2f position, sf::Texture& texture, float rotVel, float movVel)
//: m_rotVel(rotVel), m_movVel(movVel)
{
	this->m_rotVel = rotVel;
	this->m_movVel = movVel;
	this->x = 500.0f;
	this->y = 500.0f;
	this->dx = 0.0f;
	this->dy = 0.0f;
	//this->pos = position;
	m_shape.setSize(size);
	m_shape.setOrigin((m_shape.getSize().x / 2.0f), (m_shape.getSize().y / 2.0f));
	m_shape.setPosition(position);
	m_shape.setTexture(&texture);
}
void Bob::setTexture(sf::Texture& texture){
	m_shape.setTexture(&texture);
}
void Bob::setBoost(bool truth)
{
	boosting = truth;
}
void Bob::setPos()
{
	m_shape.setPosition(800, 800);
}
float Bob::getRotation() const
{
	return m_shape.getRotation(); //returns the rotation of bob
}

float Bob::getRotVel() const
{
	return m_rotVel;
}

float Bob::getMovVel() const
{
	return m_movVel;
}
sf::Vector2f Bob::getPosition() const
{
	return m_shape.getPosition();
}
void Bob::move(float x, float y)
{
	m_shape.move(sf::Vector2f(x, y));
}
void Bob::update(float time)
{

	if (boosting)
	{
		dx += sin(m_shape.getRotation() * (3.1415926 / 180));
		dy += -cos(m_shape.getRotation() * (3.1415926 / 180));
		//cout << "DY      " << dy<< endl;
	}
	else
	{
		dx *= .998;
		dy *= .998;
	}
	float maxSpeed = 1000;
	float speed = sqrt(dx * dx + dy * dy);
	//cout << "SPEED      " << speed << endl;
	if (speed > maxSpeed)
	{
		dx *= .99;
		dy *= .99;
		//cout << "MAX/SPEED      " << maxSpeed/speed << endl;
	}

	x += dx * time * 1.1;
	y += dy * time * 1.1;
	m_shape.setPosition(x, y);

	if (m_shape.getPosition().x > 2550.0f)
	{
		m_shape.setPosition(0.0f, y);
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;
	}

	if (m_shape.getPosition().y > 1800.0f)
	{
		m_shape.setPosition(x, 0.0f);
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;
	}
	if (m_shape.getPosition().x < -50.0f)
	{
		m_shape.setPosition(2550.0f, y);
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;
	}
	if (m_shape.getPosition().y < -50.0f)
	{
		m_shape.setPosition(x, 1800.0f);
		x = m_shape.getPosition().x;
		y = m_shape.getPosition().y;
	}
}
void Bob::rotate(float time)
{
	m_shape.rotate(time * m_rotVel);
}

void Bob::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

// Bullet class
Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, sf::Texture& texture, float movVel, float bRot)
//m_movVel(movVel)
{
	this->m_movVel = movVel;
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setTexture(&texture);
	m_shape.setOrigin((m_shape.getSize().x / 2.0f), (m_shape.getSize().y / 2.0f));
	m_shape.rotate(bRot);
}

float Bullet::getRotation() const
{
	return m_shape.getRotation();
}
sf::Vector2f Bullet::getPosition() const
{
	return m_shape.getPosition();
}
float Bullet::getMovVel() const
{
	return m_movVel;
}

void Bullet::move(float time)
{
	float rot = m_shape.getRotation();
	rot = rot * (3.14159265359) / 180;
	double newX = sin(rot);
	double newY = -cos(rot);
	m_shape.move(time * m_movVel * newX, time * m_movVel * newY);

	if (m_shape.getPosition().x < 2.0f)
	{
		rot = rot + 3.1415926 / 2;
	}
	if (m_shape.getPosition().y > 1498.0f)
	{
		rot = rot + 3.1415926 / 2;
	}
	if (m_shape.getPosition().y < 2.0f)
	{
		rot = rot + 3.1415926 / 2;
	}
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

Asteroid::Asteroid(sf::Vector2f position, sf::Texture& smallTex, sf::Texture& mediumTex, sf::Texture& largeTex, float movVel, int asteroidSize)
//m_movVel(movVel)
{
	this->asteroidSize = asteroidSize;
	this->m_movVel = movVel;

	m_shape.setPosition(position);

	if (asteroidSize == 1)
	{
		m_shape.setRadius(50*asteroidSize);
		m_shape.setTexture(&smallTex);
	}
	if (asteroidSize == 2)
	{
		m_shape.setRadius(50*asteroidSize);
		m_shape.setTexture(&mediumTex);
<<<<<<< HEAD
=======
				//m_shape.setTexture(&smallTex);

>>>>>>> parent of 799546d (elliot karp)
	}
	if (asteroidSize == 3)
	{
		m_shape.setRadius(50*asteroidSize);
		m_shape.setTexture(&largeTex);

	}

<<<<<<< HEAD
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
=======

	m_shape.setOrigin(50*asteroidSize , 50*asteroidSize);
	//cout << "asteroid spawned in at " << position.x << " " << position.y << endl;
>>>>>>> parent of 799546d (elliot karp)
	setRotation(); //sets the rotation to a random value
}
void Asteroid::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
}
sf::Vector2f Asteroid::getPosition() const
{
	return m_shape.getPosition();
}
float Asteroid::getMovVel() const
{
	return m_movVel;
}
int Asteroid::getInt()
{
	return asteroidSize;
}
void Asteroid::setRotation()
{

	// Generate random angle between 0 and 360 degrees
	float angle = rand() % 361;
	angle = angle * (180.0f / 3.14159265358979f);
	m_shape.setRotation(angle);
}
<<<<<<< HEAD

=======
void Asteroid::setNewRotation(float x)
{
	this->m_shape.setRotation(x);
}
void Asteroid::setTexture(sf::Texture& texture){
	m_shape.setTexture(&texture);
}
float Asteroid::getCurRotation(){
	return AsteroidRotation;
}
>>>>>>> parent of 799546d (elliot karp)
void Asteroid::move(float time)
{

	float rot = m_shape.getRotation();
	rot = rot * (3.14159265359) / 180;
	double newX = sin(rot);
	double newY = -cos(rot);
	m_shape.move(time * m_movVel * newX, time * m_movVel * newY);
	if (m_shape.getPosition().x > 2550.0f)
	{

		float y = m_shape.getPosition().y;
		m_shape.setPosition(0.0f, y);
	}

	if (m_shape.getPosition().y > 1800.0f)
	{
		float x = m_shape.getPosition().x;

		m_shape.setPosition(x, 0.0f);
	}
	if (m_shape.getPosition().x < -50.0f)
	{

		float y = m_shape.getPosition().y;
		m_shape.setPosition(2550.0f, y);
	}
	if (m_shape.getPosition().y < -50.0f)
	{
		float x = m_shape.getPosition().x;

		m_shape.setPosition(x, 1800.0f);
	}
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
	//cout << "drawn" << endl;
}
void Asteroid::update(float time, sf::RenderWindow& window)
{
	draw(window);
	move(time);
	//cout << time << endl;
}