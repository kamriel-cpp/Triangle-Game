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
void State::updateMousePositions(const sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	
	this->window->setView(this->window->getDefaultView());
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}
