#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Enemy {
private:
	sf::Sprite shape;
	sf::Texture texture;
	int type;
	int hp;
	int hpMax;
	float speed;
	int damage;
	int points;
	void initShape();
	void initTexture();
	void initVariables();
public:
	Enemy(float posX, float posY);
	virtual ~Enemy();
	const sf::FloatRect getBounds() const;
	void update();
	void render(sf::RenderTarget* target);

};