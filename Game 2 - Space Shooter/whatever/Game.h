#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include "player.h"
#include "bullet.h"
// Game engine class (wrapper class)

class Game {
private:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	Player* player;
	void initWindow();
	void initTextures();
	void initPlayer();
public:
	Game();
	virtual ~Game();
	void run();
	void updatePollEvents();
	void updateInput();
	void updateAttack();
	void update();
	void render();
};

