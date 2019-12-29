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

void GameState::initPlayer()
{
	this->player.shape.setPosition(this->dungeon.center);
}

void GameState::initEnemies()
{
	for (int i = 0; i < 100; i++)
	{
		this->enemies.push_back(Enemy(sf::Vector2f(
			this->player.shape.getPosition().x + rand() % 450 - 225,
			this->player.shape.getPosition().y + rand() % 450 - 225)));
	}
}

void GameState::initDungeon()
{
	this->dungeon.generate();
}

void GameState::initCameras()
{
	this->mainCamera.setWindow(this->window);
	this->mainCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
	this->secondCamera.setWindow(this->window);
	this->secondCamera.setViewport(sf::FloatRect(0.f, 0.f, 0.35f, 0.35f));
	this->secondCamera.zoom(1.35f);
	this->thirdCamera.setWindow(this->window);
	this->thirdCamera.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
	this->thirdCamera.zoom(20.f);
}

void GameState::initMinimap()
{
	for (auto& shape : this->dungeon.shapes)
	{
		this->minimap.shapes.push_back(sf::RectangleShape());
		this->minimap.shapes.back().setSize(shape.getSize());
		this->minimap.shapes.back().setPosition(shape.getPosition());
		this->minimap.shapes.back().setOrigin(shape.getOrigin());
		this->minimap.shapes.back().setFillColor(shape.getOutlineColor());
	}
}

void GameState::initTexts()
{
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
	this->tips.setCharacterSize(40);
	this->tips.setFont(this->font);
	this->tips.setString("Press on the W/A/S/D to control the player\nPress Q/E to zoom the camera");
	this->tips.setFillColor(sf::Color::White);
	this->tips.setOutlineThickness(1.f);
	this->tips.setOutlineColor(sf::Color::White);
	this->tips.setPosition(sf::Vector2f(
		this->window->getView().getSize().x / 2.f - this->tips.getGlobalBounds().width / 2.f,
		this->window->getView().getSize().y / 2.f - this->tips.getGlobalBounds().height / 1.f));
}

void GameState::initCinemachine()
{
	//ENABLE THIS
	this->cinemachine.setCamera(&this->mainCamera);
	this->cinemachine.setTarget(&this->player.shape);
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
		this->player.move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player.move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player.move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player.move(0.f, 1.f, dt);

	//Debug attribute component
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
		this->player.attributeComponent.updateStats(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		this->player.attributeComponent.loseEXP(this->player.attributeComponent.expNext / 10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		this->player.attributeComponent.gainEXP(this->player.attributeComponent.expNext / 10);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		this->player.attributeComponent.loseHP(this->player.attributeComponent.hpMax / 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V))
		this->player.attributeComponent.gainHP(this->player.attributeComponent.hpMax / 5);

	//Arrows to control the camera
	//Q/E to zoom
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->mainCamera.move(-1000.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->mainCamera.move(1000.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->mainCamera.move(0.f, -1000.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->mainCamera.move(0.f, 1000.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->mainCamera.zoom(1.01f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainCamera.zoom(0.99f);

	//Minimap teleportation
	//REMOVE LATER
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (sf::Mouse::getPosition(*this->window).x >= this->window->getDefaultView().getSize().x * 0.75f &&
			sf::Mouse::getPosition(*this->window).x <= this->window->getDefaultView().getSize().x &&
			sf::Mouse::getPosition(*this->window).y >= 0 &&
			sf::Mouse::getPosition(*this->window).y <= this->window->getDefaultView().getSize().y * 0.25f)
			this->player.shape.setPosition(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->thirdCamera.getView()));
}

void GameState::update(const float& dt)
{
	//Update some components
	this->updateMousePositions();
	this->updateInput(dt);
	this->player.update(dt);
	for (auto& enemy : this->enemies)
		enemy.update(dt);
	this->cinemachine.update(dt);

	//Wall checking
	char counter = 0;
	for (auto& wallChecker : this->player.wallCheckers)
	{
		for (auto& wall : this->dungeon.walls)
		{
			if (wallChecker.getGlobalBounds().intersects(wall.getGlobalBounds()))
			{
				this->player.intersectsWall = true;
				this->player.resetVelocity();
				break;
			}
			else
			{
				this->player.intersectsWall = false;
			}
		}
		if (this->player.intersectsWall)
		{
			if (counter == LEFT)
				this->player.move(50.f * dt, 0.f);
			if (counter == RIGHT)
				this->player.move(-50.f * dt, 0.f);
			if (counter == UP)
				this->player.move(0.f, 50.f * dt);
			if (counter == DOWN)
				this->player.move(0.f, -50.f * dt);
		}
		counter++;
	}

	//Players mouse tracking
	sf::Vector2f look_dir(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->mainCamera.getView())
		- this->player.shape.getPosition());

	float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
	this->player.shape.setRotation(angle);

	//Enemies player tracking
	for (auto& enemy : this->enemies)
	{
		sf::Vector2f look_dir(this->player.shape.getPosition() - enemy.shape.getPosition());

		float angle = atan2(look_dir.y, look_dir.x) * (180.f / 3.14159265358979323846f) + 90.f;
		enemy.shape.setRotation(angle);
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	//Main view
	this->window->setView(this->mainCamera.getView());
	this->dungeon.render(target);
	for (auto& enemy : this->enemies)
		enemy.render(target);
	this->player.render(target);

	//Tips
	this->window->setView(this->secondCamera.getView());
	target->draw(this->tips);

	//Minimap
	this->window->setView(this->thirdCamera.getView());
	this->minimap.render(target);

	this->player.shape.setFillColor(sf::Color::White);
	this->player.shape.setRadius(200.f);
	this->player.shape.setOrigin(sf::Vector2f(200.f, 200.f));
	this->player.render(target);
	this->player.shape.setFillColor(this->player.defaultColor);
	this->player.shape.setRadius(this->player.defaultRadius);
	this->player.shape.setOrigin(this->player.defaultOrigin);

	//Set window view to default
	this->window->setView(this->window->getDefaultView());
}
