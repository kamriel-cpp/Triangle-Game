///Initializations
void GameState::initVariables()
{
	this->wasPressedLeft = true;
	this->wasPressedRight = true;
	this->wasPressedMiddle = true;
	this->battleState = false;
	this->battleRoomIndex = 0;
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
		throw "ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT";
}

void GameState::initFloor()
{
	this->floor.generate();

	this->floorText = new sf::Text("Floor " + std::to_string(this->floor.number), this->font, 500);
	this->floorText->setOrigin(
		this->floorText->getGlobalBounds().width  / 2.f,
		this->floorText->getGlobalBounds().height / 2.f);
	this->floorText->setPosition(this->floor.startRoomPosition);
	this->floorText->scale(0.2f, 0.2f);
}

void GameState::initPlayer()
{
	this->player = new Player(this->floor.startRoomPosition);
	this->units.push_back(new Player(this->floor.startRoomPosition));
	this->units.push_back(new Enemy(this->floor.startRoomPosition, "Shooter", 1));
}

void GameState::initEnemies()
{
	///Around the player
	for (int i = 0; i < 0; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->floor.startRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
			this->floor.startRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
			std::string(rand() % 2 ? "Melee" : "Shooter"), 1));
	}

	///In the last room
	for (int i = 0; i < 0; i++)
	{
		this->enemies.push_back(new Enemy(sf::Vector2f(
			this->floor.lastRoomPosition.x + rand() % (int)(this->floor.getRoomSize().x * 0.9) - this->floor.getRoomSize().x * 0.9 / 2.f,
			this->floor.lastRoomPosition.y + rand() % (int)(this->floor.getRoomSize().y * 0.9) - this->floor.getRoomSize().y * 0.9 / 2.f),
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
	this->ui = new UserInterface(&this->font, &this->floor, this->player, this->window, this->uiView, &this->mousePosView);
}

void GameState::initWaveSpawner()
{
	this->waveSpawner = nullptr;
}

///Constructors/Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	///Initialize functions
	this->initVariables();
	this->initKeybinds();
	this->initFont();
	this->initFloor();
	this->initPlayer();
	this->initEnemies();
	this->initViews();
	this->initCameras();
	this->initUI();
	this->initWaveSpawner();
}

GameState::~GameState()
{
	delete this->ui;
	this->ui = nullptr;

	delete this->mainCamera;
	this->mainCamera = nullptr;

	delete this->uiView;
	this->uiView = nullptr;

	delete this->mainView;
	this->mainView = nullptr;

	if (this->waveSpawner)
	{
		delete this->waveSpawner;
		this->waveSpawner = nullptr;
	}

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

	while (!this->enemies.empty())
	{
		delete this->enemies.back();
		this->enemies.pop_back();
	}

	delete this->player;
	this->player = nullptr;

	delete this->floorText;
	this->floorText = nullptr;
}

///Functions
void GameState::applyDamage(const float& amount, Actor* target, Actor* caster)
{
	if (!target) return;

	if (!target->isDead())
	{
		target->blink(&this->effects);
		target->loseHP(amount);
	}

	if (caster)
		if (target->isDead())
			caster->gainEXP(sqrt(target->getLevel()) * 100);
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
	{
		if (this->player)
			this->player->shoot(this->player, &bullets);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!this->wasPressedRight)
		{
			this->wasPressedRight = true;

			#ifdef DEBUG_PLAYER_STATS_OUTPUT
			if (this->player)
				this->player->debugPrint();
			#endif

			#ifdef DEBUG_CLOSE_CURRENT_ROOM
			if (this->player)
				for (auto& room : this->floor.rooms)
					if (this->player->completelyIntersects(room->shape.getGlobalBounds()))
						this->floor.closeRoom(room->index);
			#endif
		}
	}
	else
	{
		this->wasPressedRight = false;
	}

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
	else
	{
		this->wasPressedMiddle = false;
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (!this->player->isStopped())
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

	#ifdef DEBUG_ATTRIBUTE_MANIPULATION
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
		this->player->levelUp();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
		this->player->selectAttributePoints(0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		this->player->selectAttributePoints(1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		this->player->selectAttributePoints(2);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		this->player->selectAttributePoints(3);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		this->player->selectAttributePoints(4);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
		this->player->selectAttributePoints(5);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
		this->player->selectAttributePoints(6);
	#endif
}

void GameState::updateCollisionsWithWalls(const float& dt)
{
	///Blocking player and enemies movement direction to the wall
	for (auto& room : this->floor.rooms)
	{
		for (auto& wall : room->getWalls())
		{
			///Blocking player movement direction to the wall
			if (this->player->getGlobalBounds().intersects(wall->getGlobalBounds()))
			{
				if (this->player->getSideOfCollision(wall->getGlobalBounds()) == DIR_LEFT)
				{
					this->player->stopVelocityX();
					this->player->sf::CircleShape::move(50.f * dt, 0.f);
				}
				else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == DIR_RIGHT)
				{
					this->player->stopVelocityX();
					this->player->sf::CircleShape::move(-50.f * dt, 0.f);
				}
				else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == DIR_UP)
				{
					this->player->stopVelocityY();
					this->player->sf::CircleShape::move(0.f, 50.f * dt);
				}
				else if (this->player->getSideOfCollision(wall->getGlobalBounds()) == DIR_DOWN)
				{
					this->player->stopVelocityY();
					this->player->sf::CircleShape::move(0.f, -50.f * dt);
				}
			}

			///Blocking enemy movement direction to the wall
			if (!this->enemies.empty())
			{
				for (auto& enemy : this->enemies)
				{
					if (enemy)
					{
						if (enemy->getGlobalBounds().intersects(wall->getGlobalBounds()))
						{
							if (enemy->getSideOfCollision(wall->getGlobalBounds()) == DIR_LEFT)
							{
								enemy->stopVelocityX();
								enemy->sf::CircleShape::move(50.f * dt, 0.f);
							}
							else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == DIR_RIGHT)
							{
								enemy->stopVelocityX();
								enemy->sf::CircleShape::move(-50.f * dt, 0.f);
							}
							else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == DIR_UP)
							{
								enemy->stopVelocityY();
								enemy->sf::CircleShape::move(0.f, 50.f * dt);
							}
							else if (enemy->getSideOfCollision(wall->getGlobalBounds()) == DIR_DOWN)
							{
								enemy->stopVelocityY();
								enemy->sf::CircleShape::move(0.f, -50.f * dt);
							}
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

	///Blocking player and enemies movement direction to the door
	for (auto& room : this->floor.rooms)
	{
		if (!room->getDoors().empty())
		{
			for (auto& door : room->getDoors())
			{
				///Blocking player movement direction to the door
				if (this->player->getGlobalBounds().intersects(door->getGlobalBounds()))
				{
					if (this->player->getSideOfCollision(door->getGlobalBounds()) == DIR_LEFT)
					{
						this->player->stopVelocityX();
						this->player->sf::CircleShape::move(50.f * dt, 0.f);
					}
					else if (this->player->getSideOfCollision(door->getGlobalBounds()) == DIR_RIGHT)
					{
						this->player->stopVelocityX();
						this->player->sf::CircleShape::move(-50.f * dt, 0.f);
					}
					else if (this->player->getSideOfCollision(door->getGlobalBounds()) == DIR_UP)
					{
						this->player->stopVelocityY();
						this->player->sf::CircleShape::move(0.f, 50.f * dt);
					}
					else if (this->player->getSideOfCollision(door->getGlobalBounds()) == DIR_DOWN)
					{
						this->player->stopVelocityY();
						this->player->sf::CircleShape::move(0.f, -50.f * dt);
					}
				}

				///Blocking enemy movement direction to the door
				if (!this->enemies.empty())
				{
					for (auto& enemy : this->enemies)
					{
						if (enemy)
						{
							if (enemy->getGlobalBounds().intersects(door->getGlobalBounds()))
							{
								if (enemy->getSideOfCollision(door->getGlobalBounds()) == DIR_LEFT)
								{
									enemy->stopVelocityX();
									enemy->sf::CircleShape::move(50.f * dt, 0.f);
								}
								else if (enemy->getSideOfCollision(door->getGlobalBounds()) == DIR_RIGHT)
								{
									enemy->stopVelocityX();
									enemy->sf::CircleShape::move(-50.f * dt, 0.f);
								}
								else if (enemy->getSideOfCollision(door->getGlobalBounds()) == DIR_UP)
								{
									enemy->stopVelocityY();
									enemy->sf::CircleShape::move(0.f, 50.f * dt);
								}
								else if (enemy->getSideOfCollision(door->getGlobalBounds()) == DIR_DOWN)
								{
									enemy->stopVelocityY();
									enemy->sf::CircleShape::move(0.f, -50.f * dt);
								}
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
		}
	}
}

void GameState::updateCollisionsWithBullets()
{
	///Units collisions with bullets
	if (!this->bullets.empty() && !this->enemies.empty())
	{
		///From Player to Enemies
		for (auto& bullet : this->bullets)
		{
			if (bullet)
			{
				if (typeid(*bullet->caster).name() == typeid(Player).name())
				{
					for (auto& enemy : this->enemies)
					{
						if (enemy)
						{
							if (bullet->getGlobalBounds().intersects(enemy->getGlobalBounds()))
							{
								this->applyDamage(bullet->damage, enemy, this->player);

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

		///From Enemies to Player
		for (auto& bullet : this->bullets)
		{
			if (bullet)
			{
				if (typeid(*bullet->caster).name() == typeid(Enemy).name())
				{
					if (this->player)
					{
						if (bullet->getGlobalBounds().intersects(this->player->getGlobalBounds()))
						{
							this->applyDamage(bullet->damage, this->player);

							if (!this->player->isDead())
								#ifdef DEBUG_PLAYER_DAMAGE_DETECTION
								std::cout << "DEBUG::PLAYER_DAMAGE_DETECTED" << std::endl;
								#endif
							else
								#ifdef DEBUG_PLAYER_DEATH_DETECTION
								std::cout << "DEBUG::PLAYER_DEATH_DETECTED" << std::endl;
								#endif

							bullet->explode(&this->effects);
							delete bullet;
							bullet = nullptr;
							break;
						}
					}
				}
			}
		}
		this->bullets.remove(nullptr);
	}
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
					this->waveSpawner = new WaveSpawner(room->shape.getPosition(), 250,
						rand() % 2 + 2, "Melee",
						this->player->getLevel(), rand() % 3 + 3);

					room->isVisited = true;
				}
			}
		}
	}
	if (this->battleState == true)
	{
		if (this->enemies.empty())
		{
			if (this->waveSpawner->wavesCount <= 0)
			{
				if (this->waveSpawner)
					this->waveSpawner = nullptr;
				this->battleState = false;
				this->floor.openRoom(this->battleRoomIndex);

				this->player->resetHP();
			}
			else
			{
				if (this->waveSpawner)
					this->waveSpawner->spawnWave(this->enemies);
			}
		}
	}
}

void GameState::updateUnits(const float& dt)
{
	/*
	if (this->player)
		this->player->update(dt, this->mousePosView);

	if (!this->enemies.empty())
	{
		for (auto& enemy : this->enemies)
		{
			if (enemy)
			{
				if (!enemy->isDead())
				{
					enemy->update(dt, this->player->getPosition());
					enemy->updateAutoShooting(enemy, &this->bullets);
				}
				else
				{
					enemy->explode(&this->effects);

					for (auto& effect : this->effects)
					{
						if (effect)
						{
							if (typeid(*effect).name() == typeid(Blink).name())
							{
								if (effect->getTarget() == enemy)
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
							if (bullet->caster == enemy)
							{
								delete bullet;
								bullet = nullptr;
							}
						}
					}
					this->bullets.remove(nullptr);

					delete enemy;
					enemy = nullptr;
				}
			}
		}
		this->enemies.remove(nullptr);
	}
	*/
	for (auto& unit : this->units)
	{
		if (typeid(*unit).name() == typeid(Player).name())
		{
			unit->update(dt, this->mousePosView);
		}
		else if (typeid(*unit).name() == typeid(Enemy).name())
		{
			unit->update(dt, this->units.front()->getPosition());
			unit->updateAutoShooting(unit, &this->bullets);
		}
	}
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
		target->draw(*unit);

	//for (auto& enemy : this->enemies)
	//	target->draw(*enemy);
	//
	//#ifdef DEBUG_SHOW_COLLISIONCHECKERS
	//for (auto& enemy : this->enemies)
	//	enemy->renderCollisionCheckers(target);
	//#endif
	//
	//target->draw(*this->player);
	//
	//#ifdef DEBUG_SHOW_COLLISIONCHECKERS
	//this->player->renderCollisionCheckers(target);
	//#endif
	
	for (auto& effect : this->effects)
		effect->render(this->window);

	///UI
	target->setView(*this->uiView);
	this->ui->render(target);

	///Set window view to default
	target->setView(target->getDefaultView());
}
