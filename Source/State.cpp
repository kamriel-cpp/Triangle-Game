//Constructors/Destructors
State::State(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->quit = false;
	this->states = states;
}

State::~State()
{
	
}

//Functions
const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::coutMousePosView()
{
	std::cout << "(" << this->mousePosView.x << "," << this->mousePosView.y << ")" << std::endl;
}
