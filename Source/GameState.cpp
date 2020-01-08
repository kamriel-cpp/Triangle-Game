//Initializations
void GameState::initKeybinds()
{
	std::ifstream ifs("../Config/GameStateKeybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void GameState::initTexts()
{
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
}

void GameState::initFloor()
{
	this->floor.generate();

	this->floorText = new sf::Text("Floor " + std::to_string(this->floor.number), this->font, 500);
	this->floorText->setPosition(this->floor.startRoomPosition);
	this->floorText->setOrigin(
		this->floorText->getGlobalBounds().width  / 2.f,
		this->floorText->getGlobalBounds().height / 2.f);
	this->floorText->scale(0.2f, 0.2f);
}

void GameState::initPlayer()
{
	this->player = new Player(this->floor.startRoomPosition);
}

void GameState::initEnemies()
{
	///Around the player
	for (int i = 0; i < 0; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->floor.startRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
			this->floor.startRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
			sf::Color(rand() % 2 ?(rand() % 2 ? sf::Color(250, 250, 50) : sf::Color(250, 50, 50)) : (rand() % 2 ? sf::Color(50, 250, 50) : sf::Color(50, 50, 250)))));
	}

	///In the last room
	for (int i = 0; i < 0; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->floor.lastRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
			this->floor.lastRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
			sf::Color(rand() % 2 ?(rand() % 2 ? sf::Color(250, 250, 50) : sf::Color(250, 50, 50)) : (rand() % 2 ? sf::Color(50, 250, 50) : sf::Color(50, 50, 250)))));
	}
}

void GameState::initCameras()
{
	this->mainCamera = new Camera(this->window);
	this->mainCamera->zoom(0.5f);
	this->mainCamera->move(this->floor.startRoomPosition, 1.f);
	this->uiCamera = new Camera(this->window);
}

void GameState::initCinemachine()
{
	this->cinemachine = new Cinemachine(this->mainCamera, &this->player->shape, this->window);
	this->cinemachine->smoothing = 5.f;
}

void GameState::initMinimap()
{
	this->minimap = new Minimap(this->floor, *this->player, this->window);
}

void GameState::initFPSCounter()
{
	this->fpscounter = new FPSCounter(this->uiCamera->getSize() * 0.4f, this->font);
}

void GameState::initWaveSpawner()
{
	this->waveSpawner = new WaveSpawner(this->floor.startRoomPosition, 250, 5, "Shooter", 2);
}

///Constructors/Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	///Debug print
	if (debugMode)
		if (debugConsoleOutput)
			std::cout << "Starting GameState" << std::endl;

	///Initialize functions
	this->initKeybinds();
	this->initTexts();
	this->initFloor();
	this->initPlayer();
	this->initEnemies();
	this->initCameras();
	this->initCinemachine();
	this->initMinimap();
	this->initFPSCounter();
	this->initWaveSpawner();
	
	this->wasPressedLeft = false;
	this->wasPressedRight = false;
}

GameState::~GameState()
{
	///player pointer deleting
	this->player = nullptr;
	delete this->player;

	///mainCamera pointer deleting
	this->mainCamera = nullptr;
	delete this->mainCamera;

	///uiCamera pointer deleting
	this->uiCamera = nullptr;
	delete this->uiCamera;

	///cinemachine pointer deleting
	this->cinemachine = nullptr;
	delete this->cinemachine;

	///minimap pointer deleting
	this->minimap = nullptr;
	delete this->minimap;

	///fpscounter pointer deleting
	this->fpscounter = nullptr;
	delete this->fpscounter;

	///floorText pointer deleting
	this->floorText = nullptr;
	delete this->floorText;

	///waveSpawner pointer deleting
	if (this->waveSpawner)
	{
		this->waveSpawner = nullptr;
		delete this->waveSpawner;
	}

	///enemies pointers deleting
	while (!this->enemies.empty())
	{
		delete this->enemies.back();
		this->enemies.pop_back();
	}

	///texts pointers deleting
	while (!this->texts.empty())
	{
		delete this->texts.back();
		this->texts.pop_back();
	}

	///Debug print
	if (debugMode)
		if (debugConsoleOutput)
			std::cout << "Ending GameState" << std::endl;
}

///Functions
void GameState::updateInput(const float& dt)
{
	///Quit checking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();

	///DEBUG FEATURE AttributeComponent
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		this->player->loseEXP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		this->player->gainEXP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		this->player->loseHP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
		this->player->gainHP(rand() % 100);

	///DEBUG FEATURE Camera
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->mainCamera->move(-1000.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->mainCamera->move(1000.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->mainCamera->move(0.f, -1000.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->mainCamera->move(0.f, 1000.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainCamera->setSize(this->window->getDefaultView().getSize());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->mainCamera->zoom(1.01f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainCamera->zoom(0.99f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->wasPressedLeft)
		{
			this->wasPressedLeft = true;
			this->waveSpawner->spawnWave(this->enemies);
		}
	}
	else
	{
		this->wasPressedLeft = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!this->wasPressedRight)
		{
			this->wasPressedRight = true;
			this->floor.destroy();
			if (this->floorText != nullptr)
				this->floorText = nullptr;
			this->floor.generate();
			this->floorText = new sf::Text("Floor " + std::to_string(this->floor.number), this->font, 500);
			this->floorText->setPosition(this->floor.startRoomPosition);
			this->floorText->setOrigin(
				this->floorText->getGlobalBounds().width  / 2.f,
				this->floorText->getGlobalBounds().height / 2.f);
			this->floorText->scale(0.2f, 0.2f);
			if (this->minimap != nullptr)
				this->minimap = nullptr;
			this->minimap = new Minimap(this->floor, *this->player, this->window);
		}
	}
	else
	{
		this->wasPressedRight = false;
	}

	///Dashing prototype
	//if (!this->player->isDashing)
	//{
	//	///Dashing activating
	//	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	//	{
	//		this->player->isDashing = true;
	//		this->player->timeBuffer = this->player->clock.getElapsedTime().asSeconds();
	//		this->player->setMaxVelocity(this->player->defaultMaxVelocity * 2.f);
	//	}
	//}
	//else if (this->player->clock.getElapsedTime().asSeconds() - 0.3f > this->player->timeBuffer)
	//{
	//	///Dashing deactivating
	//	this->player->isDashing = false;
	//	this->player->timeBuffer = 0.f;
	//	this->player->setMaxVelocity(this->player->defaultMaxVelocity);
	//}
}

void GameState::updatePlayerInput(const float& dt)
{
	///Update player input
	if (!this->player->isDashing)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
			this->player->move(-1.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
			this->player->move(1.f, 0.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
			this->player->move(0.f, -1.f, dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
			this->player->move(0.f, 1.f, dt);
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->mainCamera->getView());
	this->updateInput(dt);

	///If not paused
	this->updatePlayerInput(dt);

	this->player->update(dt, this->mousePosView);
	for (auto& enemy : this->enemies)
		enemy->update(dt, this->player->shape.getPosition());
	this->cinemachine->update(dt);
	this->minimap->update(dt);
	this->fpscounter->update();

	///Update wall collisions
	for (auto& wall : this->floor.walls)
	{
		///Checking for player collisions with a walls
		if (this->player->intersects(wall->getGlobalBounds()))
		{
			if (this->player->getSideOfCollision(wall->getGlobalBounds()) == LEFT)
			{
				this->player->resetVelocityX();
				this->player->move(50.f * dt, 0.f);
			}
			else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == RIGHT)
			{
				this->player->resetVelocityX();
				this->player->move(-50.f * dt, 0.f);
			}
			else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == UP)
			{
				this->player->resetVelocityY();
				this->player->move(0.f, 50.f * dt);
			}
			else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == DOWN)
			{
				this->player->resetVelocityY();
				this->player->move(0.f, -50.f * dt);
			}
		}

		//Checking for enemies collisions with a walls
		for (auto& enemy : this->enemies)
		{
			if (enemy->intersects(wall->getGlobalBounds()))
			{
				if (enemy->getSideOfCollision(wall->getGlobalBounds()) == LEFT)
				{
					enemy->resetVelocityX();
					enemy->move(50.f * dt, 0.f);
				}
				else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == RIGHT)
				{
					enemy->resetVelocityX();
					enemy->move(-50.f * dt, 0.f);
				}
				else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == UP)
				{
					enemy->resetVelocityY();
					enemy->move(0.f, 50.f * dt);
				}
				else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == DOWN)
				{
					enemy->resetVelocityY();
					enemy->move(0.f, -50.f * dt);
				}
			}
		}
	}

	///Maybe remove later, but it's looking not bad
	if (debugMode)
		if (!debugCollisionsWithEnemies)
			for (auto& enemy : this->enemies)
			{
				///Checking for enemy collisions with a player
				if (enemy->intersects(this->player->shape.getGlobalBounds()))
				{
					if (enemy->getSideOfCollision(this->player->shape.getGlobalBounds()) == LEFT)
					{
						enemy->resetVelocityX();
						enemy->move(1.f, 0.f, dt);
					}
					else if (enemy->getSideOfCollision(this->player->shape.getGlobalBounds()) == RIGHT)
					{
						enemy->resetVelocityX();
						enemy->move(-1.f, 0.f, dt);
					}
					else if (enemy->getSideOfCollision(this->player->shape.getGlobalBounds()) == UP)
					{
						enemy->resetVelocityY();
						enemy->move(0.f, 1.f, dt);
					}
					else if (enemy->getSideOfCollision(this->player->shape.getGlobalBounds()) == DOWN)
					{
						enemy->resetVelocityY();
						enemy->move(0.f, -1.f, dt);
					}
				}

				///Checking for player collisions with a enemies
				if (this->player->intersects(enemy->shape.getGlobalBounds()))
				{
					if (this->player->getSideOfCollision(enemy->shape.getGlobalBounds()) == LEFT)
					{
						this->player->resetVelocityX();
						this->player->move(1.f, 0.f, dt);
					}
					else if (this->player->getSideOfCollision(enemy->shape.getGlobalBounds()) == RIGHT)
					{
						this->player->resetVelocityX();
						this->player->move(-1.f, 0.f, dt);
					}
					else if (this->player->getSideOfCollision(enemy->shape.getGlobalBounds()) == UP)
					{
						this->player->resetVelocityY();
						this->player->move(0.f, 1.f, dt);
					}
					else if (this->player->getSideOfCollision(enemy->shape.getGlobalBounds()) == DOWN)
					{
						this->player->resetVelocityY();
						this->player->move(0.f, -1.f, dt);
					}
				}
			}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	///Main view
	target->setView(this->mainCamera->getView());
	this->floor.render(target);
	target->draw(*floorText);
	for (auto& enemy : this->enemies)
		enemy->render(target);
	this->player->render(target);

	///UI
	target->setView(this->uiCamera->getView());
	this->minimap->render(target);
	if (debugMode)
		if (debugShowFPSCounter)
			this->fpscounter->render(target);

	///Set window view to default
	target->setView(target->getDefaultView());
}
