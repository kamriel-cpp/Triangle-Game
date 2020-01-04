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

void GameState::initDungeon()
{
	this->dungeon.generate();
}

void GameState::initPlayer()
{
	this->player = new Player(this->dungeon.centerPosition);
}

void GameState::initEnemies()
{
	//Around the player
	for (int i = 0; i < 50; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->dungeon.startRoomPosition.x + rand() % (int)(this->dungeon.getRoomSize().x * 0.9) - this->dungeon.getRoomSize().x * 0.9 / 2.f,
			this->dungeon.startRoomPosition.y + rand() % (int)(this->dungeon.getRoomSize().y * 0.9) - this->dungeon.getRoomSize().y * 0.9 / 2.f),
			sf::Color(rand() % 2 ?(rand() % 2 ? sf::Color(250, 250, 50) : sf::Color(250, 50, 50)) : (rand() % 2 ? sf::Color(50, 250, 50) : sf::Color(50, 50, 250)))));
	}

	//In the last room
	for (int i = 0; i < 50; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->dungeon.lastRoomPosition.x + rand() % (int)(this->dungeon.getRoomSize().x * 0.9) - this->dungeon.getRoomSize().x * 0.9 / 2.f,
			this->dungeon.lastRoomPosition.y + rand() % (int)(this->dungeon.getRoomSize().y * 0.9) - this->dungeon.getRoomSize().y * 0.9 / 2.f)));
	}
}

void GameState::initCameras()
{
	this->mainCamera = new Camera(this->window);
	this->mainCamera->zoom(0.1f);
	this->secondCamera = new Camera(this->window);
	this->secondCamera->setViewport(sf::FloatRect(0.f, 0.f, 0.3f, 0.3f));
	this->secondCamera->zoom(1.f);
	this->thirdCamera = new Camera(this->window);
	this->thirdCamera->setViewport(sf::FloatRect(0.65f, 0.f, 0.3f, 0.3f));
	this->thirdCamera->zoom(7.5f);
}

void GameState::initCinemachine()
{
	this->cinemachine = new Cinemachine(this->mainCamera, &this->player->shape, this->window);
	this->cinemachine->smoothing = 5.f;
}

void GameState::initMinimap()
{
	this->minimap = new Minimap(this->dungeon, *this->player);
}

void GameState::initTexts()
{
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
	this->tips.setCharacterSize(55);
	this->tips.setFont(this->font);
	this->tips.setString("Press on the W/A/S/D to control the player\nPress Q/E to zoom the camera");
	this->tips.setOutlineThickness(2.f);
	this->tips.setOutlineColor(sf::Color::White);
	this->tips.setOrigin(sf::Vector2f(
		this->tips.getGlobalBounds().width / 2.f,
		this->tips.getGlobalBounds().height / 2.f));
}

//Constructors/Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	std::cout << "Starting GameState" << std::endl;
	this->initKeybinds();
	this->initDungeon();
	this->initPlayer();
	this->initEnemies();
	this->initCameras();
	this->initCinemachine();
	this->initMinimap();
	this->initTexts();
}

GameState::~GameState()
{
	this->player = nullptr;
	delete this->player;
	this->mainCamera = nullptr;
	delete this->mainCamera;
	this->secondCamera = nullptr;
	delete this->secondCamera;
	this->thirdCamera = nullptr;
	delete this->thirdCamera;
	this->cinemachine = nullptr;
	delete this->cinemachine;
	this->minimap = nullptr;
	delete this->minimap;
	while (!this->enemies.empty())
	{
	    delete this->enemies.back();
	    this->enemies.pop_back();
	}
	std::cout << "Ending GameState" << std::endl;
}

//Functions
void GameState::updateInput(const float& dt)
{
	//Quit checking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

	//DEBUG FEATURES
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		this->player->loseEXP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		this->player->gainEXP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		this->player->loseHP(rand() % 100);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
		this->player->gainHP(rand() % 100);

	//DEBUG FEATURES
	//Arrows to control the camera, Q/E to zoom
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
}

void GameState::update(const float& dt)
{
	//Update some components
	this->updateMousePositions();
	this->updateInput(dt);
	this->player->update(dt);
	//for (auto& enemy : this->enemies)
	//	enemy->update(dt);
	this->cinemachine->update(dt);
	this->minimap->update(dt);

	//Players mouse tracking
	sf::Vector2f look_dir(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->mainCamera->getView())
		- this->player->shape.getPosition());
	float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
	this->player->shape.setRotation(angle);

	//Enemies player tracking
	for (auto&& enemy : this->enemies)
	{
		sf::Vector2f look_dir(this->player->shape.getPosition() - enemy->shape.getPosition());
		float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
		enemy->shape.setRotation(angle);

		sf::Vector2f move_dir;
		if (this->player->shape.getPosition().x - enemy->shape.getPosition().x > 1.f)
			move_dir.x = 1.f;
		else if (this->player->shape.getPosition().x - enemy->shape.getPosition().x < -1.f)
			move_dir.x = -1.f;
		else
			move_dir.x = 0.f;

		if (this->player->shape.getPosition().y - enemy->shape.getPosition().y > 1.f)
			move_dir.y = 1.f;
		else if (this->player->shape.getPosition().y - enemy->shape.getPosition().y < -1.f)
			move_dir.y = -1.f;
		else
			move_dir.y = 0.f;

		enemy->move(move_dir.x, move_dir.y, dt);
	}

	//Wall checking for player
	char counter = 0;
	for (auto& wallChecker : this->player->wallCheckers)
	{
		for (auto& wall : this->dungeon.walls)
		{
			if (wallChecker.getGlobalBounds().intersects(wall.getGlobalBounds()))
			{
				this->player->intersectsWall = true;
				break;
			}
			else
			{
				this->player->intersectsWall = false;
			}
		}
		if (this->player->intersectsWall)
		{
			if (counter == LEFT)
			{
				this->player->resetVelocityX();
				this->player->move(50.f * dt, 0.f);
			}
			else if (counter == RIGHT)
			{
				this->player->resetVelocityX();
				this->player->move(-50.f * dt, 0.f);
			}
			else if (counter == UP)
			{
				this->player->resetVelocityY();
				this->player->move(0.f, 50.f * dt);
			}
			else if (counter == DOWN)
			{
				this->player->resetVelocityY();
				this->player->move(0.f, -50.f * dt);
			}
			wallChecker.setFillColor(sf::Color::Red);
		}
		else
			wallChecker.setFillColor(sf::Color::White);
		counter++;
	}

	//Wall checking for enemies
	for (auto& enemy : this->enemies)
	{
		char counter = 0;
		for (auto& wallChecker : enemy->wallCheckers)
		{
			for (auto& wall : this->dungeon.walls)
			{
				if (wallChecker.getGlobalBounds().intersects(wall.getGlobalBounds()))
				{
					enemy->intersectsWall = true;
					break;
				}
				else
				{
					enemy->intersectsWall = false;
				}
			}
			if (enemy->intersectsWall)
			{
				if (counter == LEFT)
				{
					enemy->resetVelocityX();
					enemy->move(50.f * dt, 0.f);
				}
				else if (counter == RIGHT)
				{
					enemy->resetVelocityX();
					enemy->move(-50.f * dt, 0.f);
				}
				else if (counter == UP)
				{
					enemy->resetVelocityY();
					enemy->move(0.f, 50.f * dt);
				}
				else if (counter == DOWN)
				{
					enemy->resetVelocityY();
					enemy->move(0.f, -50.f * dt);
				}
				wallChecker.setFillColor(sf::Color::Red);
			}
			else
				wallChecker.setFillColor(sf::Color::White);
			counter++;
		}
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//Main view
	this->window->setView(this->mainCamera->getView());
	this->dungeon.render(target);
	for (auto& enemy : this->enemies)
		enemy->render(target);
	this->player->render(target);

	//Tips
	this->window->setView(this->secondCamera->getView());
	target->draw(this->tips);

	//Minimap
	this->window->setView(this->thirdCamera->getView());
	this->minimap->render(target);

	//Set window view to default
	this->window->setView(this->window->getDefaultView());
}
