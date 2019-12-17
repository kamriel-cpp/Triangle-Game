//Initializations
void GameState::initDungeon()
{
	this->dungeon.generate();
}

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

}

void GameState::initText()
{
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
	this->text.setCharacterSize(16.f);
	this->text.setFont(this->font);
	//this->text.setString("NOPE");
	this->text.setPosition(window->getView().getSize().x - 256, window->getView().getSize().y - 128);
}

void GameState::initCamera()
{
	this->camera.setWindow(this->window);
}

//Constructors/Destructors
GameState::GameState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	:	State(window, supportedKeys, states)
{
	std::cout << "Starting GameState" << std::endl;
	this->initDungeon();
	this->initKeybinds();
	this->initPlayer();
	this->initText();
	this->initCamera();
}

GameState::~GameState()
{
	std::cout << "Ending GameState" << std::endl;
}

//Functions
void GameState::updateInput(const float& dt)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->State::endState();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->camera.move(LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->camera.move(RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->camera.move(UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->camera.move(DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->camera.zoom(IN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->camera.zoom(OUT);
}

void GameState::update(const float& dt)
{
	this->dungeon.update(dt);
	this->camera.update(dt);
	//this->updateMousePositions();
	//this->coutMousePosView();
	this->updateInput(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->dungeon.render(target);
	target->draw(text);
}
