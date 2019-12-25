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
	this->player.setPosition(this->dungeon.getCenter());
	this->player.setMousePosition(&this->mousePosWindow);
	this->player.setMousePosition2(&this->mousePosView);
}

void GameState::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(
		this->player.getPosition().x + this->player.getGlobalBounds().width * 2,
		this->player.getPosition().y));
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
	this->minimap.setShapesList(this->dungeon.getShapesList());
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
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		if (this->player.insideDungeon)
		{
			this->player.move(-1.f, 0.f, dt);
			this->player.lastMove = MOVING_LEFT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		if (this->player.insideDungeon)
		{
			this->player.move(1.f, 0.f, dt);
			this->player.lastMove = MOVING_RIGHT;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		if (this->player.insideDungeon)
		{
			this->player.move(0.f, -1.f, dt);
			this->player.lastMove = MOVING_UP;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		if (this->player.insideDungeon)
		{
			this->player.move(0.f, 1.f, dt);
			this->player.lastMove = MOVING_DOWN;
		}
	}

	/*
	 * Press Esc to exit the game
	 * Press on the arrows to control the camera
	 * Press Q/E to zoom
	 */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->mainCamera.move(LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->mainCamera.move(RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->mainCamera.move(UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->mainCamera.move(DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->mainCamera.zoom(1.01f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainCamera.zoom(0.99f);

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
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->player.update(dt);
	this->enemy.update(dt);

	this->mainCamera.setCenter(this->player.getPosition());
	this->mainCamera.update(dt);
	this->secondCamera.update(dt);
	this->thirdCamera.update(dt);

	for (auto& shape : this->dungeon.shapes)
	{
		if (this->player.getGlobalBounds().intersects(shape.getGlobalBounds()))
		{
			this->player.insideDungeon = true;
			break;
		}
		else
		{
			this->player.insideDungeon = false;
		}
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->mainCamera.updateView();
	this->dungeon.render(target);
	this->enemy.render(target);
	this->player.render(target);

	this->secondCamera.updateView();
	target->draw(this->tips);

	this->thirdCamera.updateView();
	this->minimap.render(target);
}
