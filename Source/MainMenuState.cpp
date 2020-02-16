///Initialization
void MainMenuState::initVariables()
{
	this->wasPressedLeft = true;
	this->wasPressedRight = true;
	this->wasPressedMiddle = true;
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	this->background.setFillColor({ 12, 12, 12 });
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/MainMenuStateKeybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cerr << "ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT" << std::endl;
		throw;
	}
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		this->window->getSize().x / 2, this->window->getSize().y / 2 - 100.f,
		0.f, -10.f, 150.f, 50.f,
		&this->font, "New Game", "GAME_STATE", 36,
		{ 70, 70, 70, 200 },
		{ 250, 250, 250, 250 },
		{ 20, 20, 20, 50 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 });

	this->buttons["SETTINGS"] = new Button(
		this->window->getSize().x / 2, this->window->getSize().y / 2 - 25.f,
		0.f, -10.f, 125.f, 50.f,
		&this->font, "Settings", "SETTINGS", 36,
		{ 70, 70, 70, 200 },
		{ 250, 250, 250, 250 },
		{ 20, 20, 20, 50 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 });

	this->buttons["EXIT_STATE"] = new Button(
		this->window->getSize().x / 2, this->window->getSize().y / 2 + 50.f,
		0.f, -10.f, 100.f, 50.f,
		&this->font, "Quit", "EXIT_STATE", 36,
		{ 70, 70, 70, 200 },
		{ 250, 250, 250, 250 },
		{ 20, 20, 20, 50 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 });
}

///Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window,std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	:	State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initKeybinds();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;
}

///Functions
///Update
void MainMenuState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("NEW_GAME"))))
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
}

void MainMenuState::updateButtons()
{
	///Update mouse position
	this->updateMousePositions();

	///Updates all the buttons in the state and handles their functionality
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	///New game
	if (this->buttons["GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));

	///Settings there

	///Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
		this->State::endState();
}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateButtons();
}

///Render
void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	for (auto &it : this->buttons)
		it.second->render(target);
}
