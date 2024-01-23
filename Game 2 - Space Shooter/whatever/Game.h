#pragma once
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
// Game engine class (wrapper class)

class Game {
private:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	Player* player;
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	sf::Font font;
	sf::Text pointText;
	sf::Text gameOverText;
	unsigned points;
	//background
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	void initWindow();
	void initTextures();
	void initGui();
	void initWorld();
	void initVariables();
	void initPlayer();
	void initEnemies();
public:
	Game();
	virtual ~Game();
	void run();
	void updatePollEvents();
	void updateInput();
	void updateAttack();
	void updateEnemies();
	void updateGUI();
	void updateCollision();
	void updateWorld();
	void renderWorld();
	void update();
	void renderGUI();
	void render();
};

