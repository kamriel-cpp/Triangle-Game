///Initializations
void UserInterface::initMinimap()
{
	this->minimap = new Minimap(*this->floor, *this->player, this->window);
}

void UserInterface::initFPSCounter()
{
	this->fpscounter = new FPSCounter(this->view->getSize() * 0.4f, *this->font);
}

void UserInterface::initPlayerStatusPane()
{
	this->playerStatusPane = new PlayerStatusPane(this->font, this->view, this->player);
}

void UserInterface::initPlayerAttributesPane()
{
	this->playerAttributesPane = new PlayerAttributesPane(this->font, this->view, this->mousePosView, this->player);
}

///Constructors/Destructors
UserInterface::UserInterface(sf::Font* font, sf::View* view,
	sf::RenderWindow* window, sf::Vector2f* mouse_pos_view,
	Floor* floor, Player* player)
	: font(font), view(view), window(window), mousePosView(mouse_pos_view), floor(floor), player(player)
{
	this->initMinimap();
	this->initFPSCounter();
	this->initPlayerStatusPane();
	this->initPlayerAttributesPane();
}

UserInterface::~UserInterface()
{
	delete this->playerAttributesPane;
	delete this->playerStatusPane;
	delete this->fpscounter;
	delete this->minimap;

	this->fpscounter = nullptr;
	this->minimap = nullptr;
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

void UserInterface::update()
{
	this->minimap->update();
	this->fpscounter->update();
	this->playerStatusPane->update();
	this->playerAttributesPane->update();
}

void UserInterface::render(sf::RenderTarget* target)
{
	this->minimap->render(target);
	this->playerStatusPane->render(target);
	this->playerAttributesPane->render(target);

	#ifdef DEBUG_SHOW_FPSCOUNTER
	this->fpscounter->render(target);
	#endif
}
