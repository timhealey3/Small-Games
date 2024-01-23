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
	this->pointCount = rand() % 3 + 1; // 3 to 10
	// rand number to set texture?
	this->type = 0;
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount + 7;
	this->points = this->pointCount;
	this->speed = static_cast<float>(this->pointCount);
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

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}