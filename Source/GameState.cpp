///Initializations
void GameState::initVariables()
{
	this->wasPressedLeft = true;
	this->wasPressedRight = true;
	this->wasPressedMiddle = true;
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
	//this->mainView->zoom(0.75f);
	this->mainView->move(this->floor.startRoomPosition);

	this->uiView = new sf::View(this->window->getDefaultView());
	this->uiView->setCenter(sf::Vector2f(0.f, 0.f));
}

void GameState::initCameras()
{
	this->mainCamera = new Camera(this->mainView, this->player, this->window);
	this->mainCamera->smoothing = 5.f;
}

void GameState::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void GameState::initButtons()
{
	//float x, float y, float width, float height,
	//sf::Font* font, std::string text, unsigned char character_size,
	//sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	//sf::Color idle_color, sf::Color hover_color, sf::Color active_color
	for (int i = 0; i < 7; ++i)
		this->buttons["NUM_" + std::to_string(i)] = new Button(
			-this->uiView->getSize().x / 2 + 30.f + i * 60.f, this->uiView->getSize().y / 2 - 30.f,
			0.f, -10.f, 40.f, 40.f,
			&this->font, std::to_string(i), 36,
			sf::Color(250,250,250,200),
			sf::Color(250,250,250,250),
			sf::Color(50,250,50,250),
			sf::Color(250,250,250,10),
			sf::Color(250,250,250,20),
			sf::Color(0,0,0,0));
}

void GameState::initMinimap()
{
	this->minimap = new Minimap(this->floor, *this->player, this->window);
}

void GameState::initFPSCounter()
{
	this->fpscounter = new FPSCounter(this->uiView->getSize() * 0.4f, this->font);
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
	///Debug print
	#ifdef DEBUG_CONSOLE_OUTPUT
	std::cout << "Starting GameState" << std::endl;
	#endif

	///Initialize functions
	this->initVariables();
	this->initKeybinds();
	this->initFloor();
	this->initPlayer();
	this->initEnemies();
	this->initViews();
	this->initCameras();
	this->initFont();
	this->initButtons();
	this->initMinimap();
	this->initFPSCounter();
	this->initWaveSpawner();

	this->battleState = false;
}

GameState::~GameState()
{
	///player pointer deleting
	delete this->player;
	this->player = nullptr;

	///mainView pointer deleting
	delete this->mainView;
	this->mainView = nullptr;

	///uiView pointer deleting
	delete this->uiView;
	this->uiView = nullptr;

	///mainCamera pointer deleting
	delete this->mainCamera;
	this->mainCamera = nullptr;

	///minimap pointer deleting
	delete this->minimap;
	this->minimap = nullptr;

	///fpscounter pointer deleting
	delete this->fpscounter;
	this->fpscounter = nullptr;

	///floorText pointer deleting
	delete this->floorText;
	this->floorText = nullptr;

	///waveSpawner pointer deleting
	if (this->waveSpawner != nullptr)
	{
		delete this->waveSpawner;
		this->waveSpawner = nullptr;
	}

	///list of effects pointers deleting
	while (!this->effects.empty())
	{
		delete this->effects.back();
		this->effects.pop_back();
	}

	///list of bullets pointers deleting
	while (!this->bullets.empty())
	{
		delete this->bullets.back();
		this->bullets.pop_back();
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

	///buttons deleting
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	///Debug print
	#ifdef DEBUG_CONSOLE_OUTPUT
	std::cout << "Ending GameState" << std::endl;
	#endif
}

///Functions
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
		this->player->shoot(&bullets);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!this->wasPressedRight)
		{
			this->wasPressedRight = true;

			#ifdef DEBUG_PLAYER_STATS_OUTPUT
			this->player->statsPrint();
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
			this->initMinimap();
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
	for (auto& wall : this->floor.walls)
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
				if (enemy != nullptr)
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
				if (bullet != nullptr)
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

	///Blocking player and enemies movement direction to the door
	if (!this->floor.doors.empty())
	{
		for (auto& door : this->floor.doors)
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
					if (enemy != nullptr)
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
					if (bullet != nullptr)
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

void GameState::updateCollisionsWithBullets()
{
	///Units collisions with bullets
	if (!this->bullets.empty() && !this->enemies.empty())
	{
		for (auto& enemy : this->enemies)
		{
			for (auto& bullet : this->bullets)
			{
				if (bullet != nullptr && enemy != nullptr)
				{
					if (bullet->getGlobalBounds().intersects(enemy->getGlobalBounds()))
					{
						this->player->gainEXP(enemy->getLevel() * 10);
						
						enemy->blink(&this->effects);
						enemy->loseHP(bullet->damage);

						bullet->explode(&this->effects);
						delete bullet;
						bullet = nullptr;
					}
				}
			}
		}
	}
}

void GameState::updateCombat(const float& dt)
{
	for (auto& room : this->floor.rooms)
	{
		///If this room is not a corridor
		if (room->tag == "Hall")
		{
			///If room is not visited
			if (room->isActive)
			{
				///If player intersects with the room
				if (this->player->completelyIntersects(room->shape.getGlobalBounds()))
				{
					///Close this room
					this->floor.closeRoom(room->index);
					///Start battle
					this->battleState = true;
					///Place a new wavespawner
					if (this->waveSpawner == nullptr)
						this->waveSpawner = new WaveSpawner(room->shape.getPosition(), 250,
							rand() % 2 + 2, "Melee",
							this->player->getLevel(), rand() % 3 + 3);
				}
			}
			///If room is visited
			else
			{
				///If battle is going
				if (this->battleState == true)
				{
					///If enemies are not in the floor
					if (this->enemies.empty())
					{
						///If wavespawner alive
						if (this->waveSpawner != nullptr)
						{
							///If waves out
							if (this->waveSpawner->wavesCount <= 0)
							{
								///Destroy our wavespawner
								this->waveSpawner = nullptr;
								///Finish the battle
								this->battleState = false;
								///And open this room
								this->floor.destroyAllDoors();
							}
							else
							{
								///Spawn more enemies
								this->waveSpawner->spawnWave(this->enemies);
							}
						}
					}
				}
			}
		}
	}
}

void GameState::updateUnits(const float& dt)
{
	this->player->update(dt, this->mousePosView);
	if (!this->enemies.empty())
	{
		for (auto& enemy : this->enemies)
		{
			if (enemy != nullptr)
			{
				enemy->update(dt, this->player->getPosition());
				
				if (enemy->isDead())
				{
					enemy->explode(&this->effects);

					for (auto& effect : this->effects)
					{
						if (effect->getTarget() == enemy)
						{
							delete effect;
							effect = nullptr;
						}
					}

					delete enemy;
					enemy = nullptr;
				}
			}
		}
		this->enemies.remove(nullptr);
	}
}

void GameState::updateBullets(const float& dt)
{
	if (!this->bullets.empty())
	{
		for (auto& bullet : this->bullets)
			if (bullet != nullptr)
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
			if (effect != nullptr)
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

void GameState::updateButtons()
{
	for (auto &it : this->buttons)
		it.second->update(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), *this->uiView));

	for (int i = 0; i < 7; i++)
	{
		if (this->buttons["NUM_" + std::to_string(i)]->isPressed())
		{
			if (!this->buttons["NUM_" + std::to_string(i)]->wasPressed)
			{
				this->buttons["NUM_" + std::to_string(i)]->wasPressed = true;
				#ifdef DEBUG_BUTTONS_OUTPUT
				switch (i)
				{
				case 0:
					std::cout << "HP Max";
					break;
				case 1:
					std::cout << "ReloTime";
					break;
				case 2:
					std::cout << "Spread";
					break;
				case 3:
					std::cout << "Damage";
					break;
				case 4:
					std::cout << "BPS";
					break;
				case 5:
					std::cout << "BullSpeed";
					break;
				default:
					std::cout << "BullRadius";
					break;
				}
				if (this->player->selectAttributePoints(i))
					std::cout << " was choosed!" << std::endl;
				else
					std::cout << " cannot be choosed!" << std::endl;
				#else
				this->player->selectAttributePoints(i);
				#endif
			}
		}
		else
		{
			this->buttons["NUM_" + std::to_string(i)]->wasPressed = false;
		}
	}
}

void GameState::updateCameras(const float& dt)
{
	this->mainCamera->update(dt);
}

void GameState::updateUI(const float& dt)
{
	this->minimap->update(dt);
	this->fpscounter->update();
	this->updateButtons();
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
	this->updateUI(dt);
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
	for (auto& enemy : this->enemies)
		target->draw(*enemy);
	target->draw(*this->player);
	for (auto& effect : this->effects)
		effect->render(this->window);

	///UI
	target->setView(*this->uiView);
	this->minimap->render(target);
	#ifdef DEBUG_SHOW_FPSCOUNTER
	this->fpscounter->render(target);
	#endif
	for (auto &it : this->buttons)
		it.second->render(target);

	///Set window view to default
	target->setView(target->getDefaultView());
}
