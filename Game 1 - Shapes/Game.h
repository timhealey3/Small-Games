#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

// Game engine class (wrapper class)

class Game {
public:
	// constructors / destructors
	Game();
	virtual ~Game();
	// accesors
	const bool getWindowIsOpen() const;
	const bool getEndGame() const;
	// functions
	void spawnEnemy();
	void updateEvents();
	void updateMousePostions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	// mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	// game logic
	bool endGame;
	unsigned points;
	int health;
	float speed;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	// game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	// func
	void initVariables();
	void initWindows();
	void initEnemies();
};

