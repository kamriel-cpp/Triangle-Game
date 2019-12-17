//Initialization
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	this->background.setFillColor(sf::Color(12,12,12));
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("../Fonts/Dosis-Light.ttf"))
		throw "ERROR::MAIN_MENU_STATE::COULD_NOT_LOAD_FONT";
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("../Config/MainMenuStateKeybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
			this->keybinds[key] = this->supportedKeys->at(key2);
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		this->window->getSize().x / 2 - 75.f, this->window->getSize().y / 2 - 100.f, 150.f, 50.f,
		&this->font, "New Game", 36,
		sf::Color(70,70,70,200),
		sf::Color(250,250,250,250),
		sf::Color(20,20,20,50),
		sf::Color(20,40,20,0),
		sf::Color(20,50,20,0),
		sf::Color(20,40,20,0));

	this->buttons["SETTINGS"] = new Button(
		this->window->getSize().x / 2 - 62.5f, this->window->getSize().y / 2 - 25.f, 125.f, 50.f,
		&this->font, "Settings", 36,
		sf::Color(70,70,70,200),
		sf::Color(250,250,250,250),
		sf::Color(20,20,20,50),
		sf::Color(20,20,40,0),
		sf::Color(20,20,50,0),
		sf::Color(20,20,40,0));

	this->buttons["EXIT_STATE"] = new Button(
		this->window->getSize().x / 2 - 50.f, this->window->getSize().y / 2 + 50.f, 100.f, 50.f,
		&this->font, "Quit", 36,
		sf::Color(70,70,70,200),
		sf::Color(250,250,250,250),
		sf::Color(20,20,20,50),
		sf::Color(40,20,20,0),
		sf::Color(40,20,20,0),
		sf::Color(50,20,20,0));
}

//Constructors/Destructors
MainMenuState::MainMenuState(sf::RenderWindow* window,std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	:	State(window, supportedKeys, states)
{
	std::cout << "Starting MainMenuState!" << std::endl;

	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	std::cout << "Ending MainMenuState!" << std::endl;
}

//Functions
//Update
void MainMenuState::updateInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("NEW_GAME"))))
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Settings

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->State::endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

//Render
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto &it : this->buttons)
		it.second->render(target);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(this->background);
	this->renderButtons(target);

	/*//REMOVE LATER
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(18);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}
