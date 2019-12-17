//Initialization
void Application::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Application::initWindow()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "Dungeon Generation";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

	this->fullscreen = true;
	this->windowSettings.antialiasingLevel = 0;

	if (this->fullscreen)
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Application::initDungeon()
{
	this->dungeon.generate();
}

void Application::initText()
{
	this->font.loadFromFile("../Fonts/Dosis-Light.ttf");
	this->tips.setCharacterSize(40.f);
	this->tips.setFont(this->font);
	this->tips.setString("Press on the arrows to control the camera\nPress Q/E to zoom");
	this->tips.setFillColor(sf::Color::White);
	this->tips.setPosition(sf::Vector2f(
		this->window->getView().getSize().x / 2.f - this->tips.getGlobalBounds().width / 2.f,
		this->window->getView().getSize().y / 2.f - this->tips.getGlobalBounds().height / 2.f));
}

void Application::initMainCamera()
{
	this->mainCamera.setWindow(this->window);
	this->secondaryCamera.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

void Application::initSecondaryCamera()
{
	this->secondaryCamera.setWindow(this->window);
	this->secondaryCamera.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
}

//Constructors/Destructors
Application::Application()
{
	std::cout << "Starting Application" << std::endl;
	this->initVariables();
	this->initWindow();
	this->initDungeon();
	this->initText();
	this->initMainCamera();
	this->initSecondaryCamera();
}

Application::~Application()
{
	delete this->window;
	this->endApplication();
}

//Functions
void Application::endApplication()
{
	std::cout << "Ending Application" << std::endl;
}

//Update
void Application::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Application::updateEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Application::updateInput()
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		this->window->close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->mainCamera.move(LEFT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->mainCamera.move(RIGHT);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->mainCamera.move(UP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->mainCamera.move(DOWN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		this->mainCamera.zoom(IN);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->mainCamera.zoom(OUT);
}

void Application::update()
{
	this->updateEvents();
	this->updateInput();
	this->dungeon.update(this->dt);
	this->mainCamera.update(this->dt);
	this->secondaryCamera.update(this->dt);
}

//Render
void Application::render()
{
	this->window->clear();

	this->mainCamera.render();
	this->dungeon.render(this->window);

	this->secondaryCamera.render();
	this->window->draw(this->tips);

	this->window->display();
}

//Core
void Application::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}