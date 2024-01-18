#include "Game.h"
#include "windows.h"
// private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Shooter", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/laser.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}

Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
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
}

void Game::run()
{
	while (this->window->isOpen()) {
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
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

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();
	this->player->update();
	this->updateAttack();
}

void Game::render()
{
	this->window->clear();
	// draw stuff
	this->player->render(*this->window);
	for (auto* i : this->bullets) {
		i->render(this->window);
	}
	this->window->display();
}
