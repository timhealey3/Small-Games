#include "Game.h"
#include "windows.h"
// private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/laser.png");
}

void Game::initGui()
{
	// Load font
	if (!this->font.loadFromFile("Font/scfont.ttf"))
		std::cout << "ERROR::GAME::FAILED LOAD FONT" << "\n";
	this->pointText.setPosition(600.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	// put at center of screen
	this->gameOverText.setPosition(this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f, this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background.png")) {
		std::cout << "ERROR Loading Background" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initVariables()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 25.f;
	this->spawnTimer = this->spawnTimerMax;
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGui();
	this->initWorld();
	this->initVariables();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
	// delete textures
	for (auto& i : this->textures) {
		delete i.second;
	}
	// delete all bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	// delete enemies
	for (auto* j : this->enemies) {
		delete j;
	}
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->updatePollEvents();
		if (this->player->getHp() > 0)
			this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	// move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
	// shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], 
			this->player->getPos().x + this->player->getBounds().width/2.f, 
			this->player->getPos().y, 0.f, -1.f, 5.f));
	}

}

void Game::updateAttack()
{
	int counter = 0;
	for (auto* i : this->bullets) {
		i->update();
		// delete when top of screen
		if (i->getBounds().top + i->getBounds().height < 0.f) {
			// delete bullet
			delete this->bullets.at(counter);
			// delete pointer in array
			this->bullets.erase(this->bullets.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	// spawn enemies
	if (this->spawnTimer >= this->spawnTimerMax) {
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 50.f, -100.f));
		this->spawnTimer = 0.f;
	}
	for (int i = 0; i < this->enemies.size(); i++) {
		bool enemy_removed = false;
		this->enemies[i]->update();
		// remove bullets and enemies contact
		for (size_t k = 0; k < this->bullets.size() && !enemy_removed; k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getBounds())) {
				this->points += this->enemies[i]->getPoints();
				this->bullets.erase(this->bullets.begin() + k);
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
		if (!enemy_removed && this->enemies[i]->getBounds().intersects(this->player->getBounds())) {
			this->player->loseHp(this->enemies.at(i)->getDamage());
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;
		}
		// remove enemies
		if (!enemy_removed) {
			if (this->enemies[i]->getBounds().top > this->window->getSize().y) {
				this->enemies.erase(this->enemies.begin() + i);
				enemy_removed = true;
			}
		}
	}

}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f* hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f) { // left
		this->player->setPosition(0.f, this->player->getBounds().top);
	}	
	else if (this->player->getBounds().top < 1.f) {	// top
		this->player->setPosition(this->player->getBounds().left, 1.f);
	}
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x) { // right
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) { // bottom
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
	
}

void Game::updateWorld()
{
}

void Game::update()
{
	this->updateInput();
	this->player->update();
	this->updateCollision();
	this->updateAttack();
	this->updateEnemies();
	this->updateGUI();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();
	this->renderWorld();
	// draw stuff
	this->player->render(*this->window);
	for (auto *i : this->bullets) {
		i->render(this->window);
	}
	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}
	this->renderGUI();
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);
	this->window->display();
}
