#include "player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->attackCooldownMax = 8.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	// laod a texture from file
	if (!this->texture.loadFromFile("Textures/battlecruiser.png")) {
		std::cout << "Player::Texture initilized failed" << "\n";
	}
}

void Player::initSprite()
{
	// set texture to sprite
	this->sprite.setTexture(this->texture);
	// resize
	this->sprite.scale(0.15f, 0.15f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}	

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateCooldown()
{
	if (this->attackCooldown < this->attackCooldownMax) {
		this->attackCooldown += 0.5f;
	}
}

void Player::update()
{
	this->updateCooldown();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

