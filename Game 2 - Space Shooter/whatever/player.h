#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Player();
	virtual ~Player();
	const sf::FloatRect getBounds() const;
	const sf::Vector2f& getPos() const;
	void setPosition(const float x, const float y);
	void move(const float dirX, const float dirY);
	const bool canAttack();
	void updateCooldown();
	void update();
	void render(sf::RenderTarget& target);
};