///Initializations
void UserInterface::initButtons()
{
	for (int i = 0; i < 7; ++i)
		this->buttons["NUM_" + std::to_string(i)] = new Button(
			-this->view->getSize().x / 2 + 30.f + i * 60.f, this->view->getSize().y / 2 - 30.f,
			0.f, -10.f, 40.f, 40.f,
			this->font, std::to_string(i), 36,
			{ 250, 250, 250, 200 },
			{ 250, 250, 250, 250 },
			{ 50, 250, 50, 250 },
			{ 250, 250, 250, 10 },
			{ 250, 250, 250, 20 },
			{ 0, 0, 0, 0 });
}

void UserInterface::initMinimap()
{
	this->minimap = new Minimap(*this->floor, *this->player, this->window);
}

void UserInterface::initFPSCounter()
{
	this->fpscounter = new FPSCounter(this->view->getSize() * 0.4f, *this->font);
}

void UserInterface::initStatusBars()
{
	this->hpBar = new StatusBar(sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f),
		sf::Vector2f(200.f, 20.f),
		0.25f,
		{ 50, 50, 50 },
		{ 50, 250, 50 },
		{ 250, 50, 50 });

	this->reloadBar = new StatusBar(sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f + 30.f),
		sf::Vector2f(200.f, 20.f),
		1.f,
		{ 50, 50, 50 },
		{ 50, 50, 250 },
		{ 50, 50, 150 });

	this->expBar = new StatusBar(sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f + 60.f),
		sf::Vector2f(200.f, 20.f),
		0.f,
		{ 50, 50, 50 },
		{ 150, 50, 250 },
		{ 50, 50, 50 });
}

///Constructors/Destructors
UserInterface::UserInterface(sf::Font* font,
	Floor* floor, Player* player, sf::RenderWindow* window,
	sf::View* view,
	sf::Vector2f* mouse_pos_view)
	: font(font), floor(floor), player(player), window(window), view(view), mousePosView(mouse_pos_view)
{
	this->initButtons();
	this->initMinimap();
	this->initFPSCounter();
	this->initStatusBars();
}

UserInterface::~UserInterface()
{
	delete this->expBar;
	this->expBar = nullptr;

	delete this->reloadBar;
	this->reloadBar = nullptr;

	delete this->hpBar;
	this->hpBar = nullptr;

	delete this->fpscounter;
	this->fpscounter = nullptr;

	delete this->minimap;
	this->minimap = nullptr;

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	while (!this->texts.empty())
	{
		delete this->texts.back();
		this->texts.pop_back();
	}

	this->mousePosView = nullptr;
	this->view = nullptr;
	this->window = nullptr;
	this->player = nullptr;
	this->floor = nullptr;
	this->font = nullptr;
}

///Functions
void UserInterface::rebuildMinimap()
{
	delete this->minimap;
	this->minimap = new Minimap(*this->floor, *this->player, this->window);
}

void UserInterface::updateButtons()
{
	for (auto &it : this->buttons)
		it.second->update(*this->mousePosView);

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

void UserInterface::update()
{
	this->updateButtons();
	this->minimap->update();
	this->fpscounter->update();
	this->hpBar->update((float)this->player->getHP() / (float)this->player->getHPMax());
	this->reloadBar->update((float)this->player->getReloadTimer() / (float)this->player->getReloadTime());
	this->expBar->update((float)this->player->getEXP() / (float)this->player->getEXPNext());
}

void UserInterface::render(sf::RenderTarget* target)
{
	this->minimap->render(target);
	for (auto &it : this->buttons)
		it.second->render(target);

	#ifdef DEBUG_SHOW_FPSCOUNTER
	this->fpscounter->render(target);
	#endif

	this->hpBar->render(target);
	this->reloadBar->render(target);
	this->expBar->render(target);
}
