///Initializations
void GameState::initVariables()
{
	this->waveSpawner = nullptr;
	this->wasPressedLeft = true;
	this->wasPressedRight = true;
	this->wasPressedMiddle = true;
	this->battleState = false;
	this->battleRoomIndex = 0;
	this->enemiesCounter = 0;
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/GameStateKeybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void GameState::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cerr << "ERROR::GAMESTATE::COULD_NOT_LOAD_FONT" << std::endl;
		throw;
	}
}

void GameState::initFloor()
{
	this->floorText = nullptr;
	this->floor.generate();

	if (this->floorText) delete this->floorText;
	this->floorText = new sf::Text("Floor " + std::to_string(this->floor.number), this->font, 500);
	this->floorText->setOrigin(
		this->floorText->getGlobalBounds().width  / 2.f,
		this->floorText->getGlobalBounds().height / 2.f);
	this->floorText->setPosition(this->floor.startRoomPosition);
	this->floorText->scale(0.2f, 0.2f);
}

void GameState::initPlayer()
{
	this->units.push_back(new Player(this->floor.startRoomPosition));
	this->player = (Player*)this->units.back();
}

void GameState::initEnemies()
{
	///Around the player
	for (int i = 0; i < 0; i++)
	{
		this->units.push_back(new Enemy(
			sf::Vector2f(
				this->floor.startRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
				this->floor.startRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
			std::string(rand() % 2 ? "Melee" : "Shooter"), 1));
	}

	///In the last room
	for (int i = 0; i < 0; i++)
	{
		this->units.push_back(new Enemy(
			sf::Vector2f(
				this->floor.startRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
				this->floor.startRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
			std::string(rand() % 2 ? "Melee" : "Shooter"), 1));
	}
}

void GameState::initViews()
{
	this->mainView = new sf::View(this->window->getDefaultView());
	this->mainView->setCenter(sf::Vector2f(0.f, 0.f));
	this->mainView->zoom(0.8f);
	this->mainView->move(this->floor.startRoomPosition);

	this->uiView = new sf::View(this->window->getDefaultView());
	this->uiView->setCenter(sf::Vector2f(0.f, 0.f));
}

void GameState::initCameras()
{
	this->mainCamera = new Camera(this->mainView, this->player, this->window);
	this->mainCamera->smoothing = 5.f;
}

void GameState::initUI()
{
	this->ui = new UserInterface(&this->font, this->uiView, this->window, &this->mousePosView, &this->floor, this->player);
}

///Constructors/Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initKeybinds();
	this->initFont();
	this->initFloor();
	this->initPlayer();
	this->initEnemies();
	this->initViews();
	this->initCameras();
	this->initUI();
}

GameState::~GameState()
{
	delete this->ui;
	delete this->mainCamera;
	delete this->uiView;
	delete this->mainView;
	if (this->floorText) delete this->floorText;
	if (this->waveSpawner) delete this->waveSpawner;

	while (!this->bullets.empty())
	{
		delete this->bullets.back();
		this->bullets.pop_back();
	}

	while (!this->effects.empty())
	{
		delete this->effects.back();
		this->effects.pop_back();
	}

	while (!this->units.empty())
	{
		delete this->units.back();
		this->units.pop_back();
	}

	this->ui = nullptr;
	this->mainCamera = nullptr;
	this->uiView = nullptr;
	this->mainView = nullptr;
	this->floorText = nullptr;
	this->waveSpawner = nullptr;
	this->player = nullptr;
}

///Functions
void GameState::applyDamage(const float& amount, Unit* target, Unit* caster)
{
	target->blink(&this->effects);
	target->loseHP(amount);

	if (target->isDead())
		caster->gainEXP(sqrt(target->getLVL()) * 100);
}

const bool GameState::canApplyDamage(Unit* target, Unit* caster) const
{
	return target && caster && !target->isDead() && typeid(*target).name() != typeid(*caster).name();
}

void GameState::updateInput(const float& dt)
{
	///Quit checking
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();

	#ifdef DEBUG_MAINVIEW_MANIPULATION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->mainView->move(-1000.f * dt, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->mainView->move(1000.f * dt, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->mainView->move(0.f, -1000.f * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->mainView->move(0.f, 1000.f * dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainView->setSize(this->window->getDefaultView().getSize());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->mainView->zoom(1.01f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainView->zoom(0.99f);
	#endif

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->player)
			this->player->shoot(&bullets);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!this->wasPressedRight)
		{
			this->wasPressedRight = true;

			#ifdef DEBUG_PLAYER_STATS_OUTPUT
			if (this->player)
				this->player->debugStatsPrint();
			#endif

			#ifdef DEBUG_CLOSE_CURRENT_ROOM
			if (this->player)
				for (auto& room : this->floor.rooms)
					if (this->player->completelyIntersects(room->shape.getGlobalBounds()))
						this->floor.closeRoom(room->index);
			#endif
		}
	}
	else this->wasPressedRight = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		if (!this->wasPressedMiddle)
		{
			this->wasPressedMiddle = true;

			///Go to next floor
			///without player teleportation to the start room
			#ifdef DEBUG_REBUILD_FLOOR
			this->floor.destroy();
			this->initFloor();
			this->ui->rebuildMinimap();
			#endif
		}
	}
	else this->wasPressedMiddle = false;
}

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);
		
	#ifdef DEBUG_ATTRIBUTE_MANIPULATION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		this->player->lvlUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
		this->player->manualDistributeAPS(UAT_MHP);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		this->player->manualDistributeAPS(UAT_SPS);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		this->player->manualDistributeAPS(UAT_SPR);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		this->player->manualDistributeAPS(UAT_DMG);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		this->player->manualDistributeAPS(UAT_BPS);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
		this->player->manualDistributeAPS(UAT_BSP);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
		this->player->manualDistributeAPS(UAT_BRD);
	#endif
}

void GameState::updateCollisionsWithWalls(const float& dt)
{
	///Blocking units movement direction to the wall
	for (auto& room : this->floor.rooms)
	{
		for (auto& wall : room->getWalls())
		{
			for (auto& unit : this->units)
			{
				if (unit)
				{
					if (unit->getGlobalBounds().intersects(wall->getGlobalBounds()))
					{
						if (unit->getSideOfCollision(wall->getGlobalBounds()) == DIR_LEFT)
						{
							unit->stopVelocityX();
							unit->sf::CircleShape::move(50.f * dt, 0.f);
						}
						else if (unit->getSideOfCollision(wall->getGlobalBounds()) == DIR_RIGHT)
						{
							unit->stopVelocityX();
							unit->sf::CircleShape::move(-50.f * dt, 0.f);
						}
						else if (unit->getSideOfCollision(wall->getGlobalBounds()) == DIR_UP)
						{
							unit->stopVelocityY();
							unit->sf::CircleShape::move(0.f, 50.f * dt);
						}
						else if (unit->getSideOfCollision(wall->getGlobalBounds()) == DIR_DOWN)
						{
							unit->stopVelocityY();
							unit->sf::CircleShape::move(0.f, -50.f * dt);
						}
					}
				}
			}

			///Explode bullet
			if (!this->bullets.empty())
			{
				for (auto& bullet : this->bullets)
				{
					if (bullet)
					{
						if (bullet->getGlobalBounds().intersects(wall->getGlobalBounds()))
						{
							bullet->explode(&this->effects);
							delete bullet;
							bullet = nullptr;
						}
					}
				}
			}
		}
	}

	///Blocking units movement direction to the door
	for (auto& room : this->floor.rooms)
	{
		for (auto& door : room->getDoors())
		{
			for (auto& unit : this->units)
			{
				if (unit)
				{
					if (unit->getGlobalBounds().intersects(door->getGlobalBounds()))
					{
						if (unit->getSideOfCollision(door->getGlobalBounds()) == DIR_LEFT)
						{
							unit->stopVelocityX();
							unit->sf::CircleShape::move(50.f * dt, 0.f);
						}
						else if (unit->getSideOfCollision(door->getGlobalBounds()) == DIR_RIGHT)
						{
							unit->stopVelocityX();
							unit->sf::CircleShape::move(-50.f * dt, 0.f);
						}
						else if (unit->getSideOfCollision(door->getGlobalBounds()) == DIR_UP)
						{
							unit->stopVelocityY();
							unit->sf::CircleShape::move(0.f, 50.f * dt);
						}
						else if (unit->getSideOfCollision(door->getGlobalBounds()) == DIR_DOWN)
						{
							unit->stopVelocityY();
							unit->sf::CircleShape::move(0.f, -50.f * dt);
						}
					}
				}
			}

			///Explode bullet
			for (auto& bullet : this->bullets)
			{
				if (bullet)
				{
					if (bullet->getGlobalBounds().intersects(door->getGlobalBounds()))
					{
						bullet->explode(&this->effects);
						delete bullet;
						bullet = nullptr;
					}
				}
			}
		}
	}
	this->bullets.remove(nullptr);
	this->units.remove(nullptr);
}

void GameState::updateCollisionsWithBullets()
{
	///Units collisions with bullets
	for (auto& bullet : this->bullets)
	{
		if (bullet)
		{
			for (auto& unit : this->units)
			{
				if (unit)
				{
					if (bullet->getGlobalBounds().intersects(unit->getGlobalBounds()))
					{
						if (this->canApplyDamage(unit, bullet->caster))
						{
							this->applyDamage(bullet->damage, unit, bullet->caster);
							bullet->explode(&this->effects);
							delete bullet;
							bullet = nullptr;
							break;
						}
					}
				}
			}
		}
	}
	this->bullets.remove(nullptr);
}

void GameState::updateEnemiesCounter(const float& dt)
{
	this->enemiesCounter = 0;
	for (auto& unit : this->units)
		if (typeid(*unit).name() == typeid(Enemy).name())
			this->enemiesCounter++;
}

void GameState::updateCombat(const float& dt)
{
	for (auto& room : this->floor.rooms)
	{
		if (room->tag == RT_HALL_MAIN || room->tag == RT_HALL_SECONDARY)
		{
			if (!room->isVisited)
			{
				if (this->player->completelyIntersects(room->shape.getGlobalBounds()))
				{
					this->battleState = true;
					this->battleRoomIndex = room->index;
					this->floor.closeRoom(this->battleRoomIndex);
					this->waveSpawner = new WaveSpawner(
						room->shape.getPosition(), 250,
						rand() % 2 + 2, "Melee",
						this->player->getLVL(), rand() % 3 + 3);

					room->isVisited = true;
				}
			}
		}
	}
	
	if (this->battleState == true)
	{
		if (!this->enemiesCounter)
		{
			if (this->waveSpawner->canSpawnWave())
			{
				this->waveSpawner->spawnWave(this->units);
			}
			else
			{
				if (this->waveSpawner)
					this->waveSpawner = nullptr;
				this->battleState = false;
				this->floor.openRoom(this->battleRoomIndex);

				this->player->resetHP();
			}
		}
	}
}

void GameState::updateUnits(const float& dt)
{
	for (auto& unit : this->units)
	{
		if (typeid(*unit).name() == typeid(Player).name())
		{
			unit->update(&this->bullets, this->mousePosView, dt);
		}
		else if (typeid(*unit).name() == typeid(Enemy).name())
		{
			if (unit)
			{
				if (!unit->isDead())
				{
					unit->update(&this->bullets, this->player->getPosition(), dt);
				}
				else
				{
					unit->explode(&this->effects);

					for (auto& effect : this->effects)
					{
						if (effect)
						{
							if (typeid(*effect).name() == typeid(Blink).name())
							{
								if (effect->getTarget() == unit)
								{
									delete effect;
									effect = nullptr;
								}
							}
						}
					}
					this->effects.remove(nullptr);

					for (auto& bullet : this->bullets)
					{
						if (bullet)
						{
							if (bullet->caster == unit)
							{
								delete bullet;
								bullet = nullptr;
							}
						}
					}
					this->bullets.remove(nullptr);

					delete unit;
					unit = nullptr;
				}
			}
		}
		else
		{
			std::cerr << "ERROR::DETECTED_UNKNOWN_UNIT_TYPE::" << typeid(*unit).name() << std::endl;
			throw;
		}
	}
	this->units.remove(nullptr);
}

void GameState::updateBullets(const float& dt)
{
	if (!this->bullets.empty())
	{
		for (auto& bullet : this->bullets)
			if (bullet)
				bullet->update(dt);

		this->bullets.remove(nullptr);
	}
}

void GameState::updateEffects(const float& dt)
{
	if (!this->effects.empty())
	{
		for (auto& effect : this->effects)
		{
			if (effect)
			{
				effect->update(dt);

				if (effect->isDone())
				{
					delete effect;
					effect = nullptr;
				}
			}
		}
		this->effects.remove(nullptr);
	}
}

void GameState::updateCameras(const float& dt)
{
	this->mainCamera->update(dt);
}

void GameState::updateUI()
{
	this->ui->update();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(this->mainView);
	this->updateInput(dt);
	this->updatePlayerInput(dt);
	this->updateCollisionsWithWalls(dt);
	this->updateCollisionsWithBullets();
	this->updateEnemiesCounter(dt);
	this->updateCombat(dt);
	this->updateUnits(dt);
	this->updateBullets(dt);
	this->updateEffects(dt);
	this->updateCameras(dt);
	this->updateMousePositions(this->uiView);
	this->updateUI();
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	///Main view
	target->setView(*this->mainView);
	this->floor.render(target);
	target->draw(*floorText);

	for (auto& bullet : this->bullets)
		target->draw(*bullet);

	for (auto& unit : this->units)
	{
		target->draw(*unit);
		#ifdef DEBUG_SHOW_COLLISIONCHECKERS
		unit->renderCollisionCheckers(target);
		#endif
	}
	
	for (auto& effect : this->effects)
		effect->render(this->window);

	///UI
	target->setView(*this->uiView);
	this->ui->render(target);

	///Set window view to default
	target->setView(target->getDefaultView());
}
