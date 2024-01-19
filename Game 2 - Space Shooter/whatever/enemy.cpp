#include "enemy.h"

void Enemy::initTexture()
{
	// laod a texture from file
	if (!this->texture.loadFromFile("Textures/phoenix.png")) {
		std::cout << "Player::Texture initilized failed" << "\n";
	}
}

void Enemy::initShape()
{
	// set texture to sprite
	this->shape.setTexture(this->texture);
	// resize
	this->shape.scale(0.10f, 0.12f);
}

void Enemy::initVariables()
{
	this->type = 0;
	this->hpMax = 10;
	this->hp = 0;
	this->damage = 1;
	this->points = 5;
	this->speed = 2.5f;
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initTexture();
	this->initShape();
	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{

}


void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

const sf::FloatRect Enemy::getBounds() const {
	return this->shape.getGlobalBounds();
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}