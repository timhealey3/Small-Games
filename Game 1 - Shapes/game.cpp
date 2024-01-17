#include "Game.h"

// constructors - destructors
Game::Game()
{
	this->initVariables();
	this->initWindows();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemy()
{
	// spawns enemies and sets their colors and positions
	// random color, random position, add enemy to vector
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	int randomValue = rand() % 100;
	if (randomValue < 90) {
		this->enemy.setFillColor(sf::Color::Blue);
	}
	else if (randomValue < 95)
		this->enemy.setFillColor(sf::Color::Yellow);
	else {
		this->enemy.setFillColor(sf::Color::Red);
	}
	this->enemies.push_back(this->enemy);
}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePostions()
{
	// updates mouse position relative to window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	// map to view
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	// update enemy spawn timer and spawn enemies.
	// when total amount of enemies is smaller than max
	if (this->enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			// spawn && reset timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	// move enemies
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i].move(0.f, speed);
		bool deleted = false;
		for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
			// if click on enemy
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView) && this->enemies[i].getFillColor() == sf::Color::Blue) {
				// delete enemy
				deleted = true;
				// increase points
				this->points += 10;
				speed += 0.01;
			}
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView) && this->enemies[i].getFillColor() == sf::Color::Yellow) {
				// delete enemy
				deleted = true;
				// increase points
				this->points -= 50;
				this->health -= 10;
				speed += 0.5;
			}
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView) && this->enemies[i].getFillColor() == sf::Color::Red) {
				// delete enemy
				deleted = true;
				// increase points
				this->health += 10;
				this->points += 50;
			}
			// if below screen, delete and change points
			if (this->enemies[i].getPosition().y > this->window->getSize().y && this->enemies[i].getFillColor() != sf::Color::Yellow) {
				deleted = true;
				speed += 0.5;
				health -= 10;
			}
			if (this->enemies[i].getPosition().y > this->window->getSize().y && this->enemies[i].getFillColor() == sf::Color::Yellow) {
				deleted = true;
			}
			if (deleted)
				this->enemies.erase(this->enemies.begin() + i);
		}
	}
}


void Game::update()
{
	this->updateEvents();
	// if endgame false, play game
	if (!this->endGame) {
		this->updateMousePostions();
		this->updateText();
		this->updateEnemies();
	}
	// endgame condition
	if (this->health <= 0) {
		this->endGame = true;
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n" << "Health: " << this->health;
	this->uiText.setString(ss.str());
}

void Game::renderText()
{
	this->window->draw(uiText);
}

void Game::renderEnemies()
{
	for (auto& e : this->enemies) {
		this->window->draw(e);
	}
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	this->renderEnemies();
	this->renderText();
	this->window->display();
}
// private functions
void Game::initVariables()
{
	this->endGame = false;
	this->health = 100;
	this->mouseHeld = false;
	this->window = nullptr;
	this->points = 0;
	this->speed = 1.f;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initFonts()
{
	if (this->font.loadFromFile("VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "ERROR: initFonts Failed to load font";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initWindows()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(this->videoMode), "Small Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}	

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
}