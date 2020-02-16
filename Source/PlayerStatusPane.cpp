///Initializations
void PlayerStatusPane::initTexts()
{
	this->lvlInfo = sf::Text("LVLINFO", *this->font, 20);
	this->lvlInfo.setOrigin(this->lvlInfo.getGlobalBounds().width, this->lvlInfo.getGlobalBounds().height / 2.f);
	this->lvlInfo.setPosition(-this->view->getSize().x * 0.425f + 200.f, -this->view->getSize().y * 0.4f + 45.f);
	this->lvlInfo.setFillColor(sf::Color::White);

	this->apsInfo = sf::Text("APSINFO", *this->font, 20);
	this->apsInfo.setPosition(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f + 62.5f);
	this->apsInfo.setFillColor(sf::Color::White);
}

void PlayerStatusPane::initProgressBars()
{
	this->hpBar = new ProgressBar(this->font, 20,
		sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f),
		sf::Vector2f(200.f, 20.f),
		1.5f, 34,
		{ 50, 50, 50, 50 }, { 50, 50, 50 },
		{ 50, 200, 50 }, { 200, 50, 50 },
		{ 0, 0, 0 }, { 250, 250, 250 }, IT_VALUE);

	this->reloadBar = new ProgressBar(this->font, 20,
		sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f + 25.f),
		sf::Vector2f(200.f, 20.f),
		1.5f, 100,
		{ 50, 50, 50, 50 }, { 50, 50, 50 },
		{ 50, 200, 200 }, { 0, 100, 100 },
		{ 0, 0, 0 }, { 250, 250, 250 }, IT_PERCENT);

	this->expBar = new ProgressBar(this->font, 20,
		sf::Vector2f(-this->view->getSize().x * 0.425f, -this->view->getSize().y * 0.4f + 50.f),
		sf::Vector2f(150.f, 20.f),
		1.5f, 0,
		{ 50, 50, 50, 50 }, { 50, 50, 50 },
		{ 200, 50, 200 }, { 0, 0, 0, 0 },
		{ 250, 250, 250 }, { 0, 0, 0, 0 }, IT_VALUE);
}

///Constructors/Destructors
PlayerStatusPane::PlayerStatusPane(sf::Font* font, sf::View* view, Player* player)
	: font(font), view(view), player(player)
{
	this->initTexts();
	this->initProgressBars();
}

PlayerStatusPane::~PlayerStatusPane()
{
	delete this->expBar;
	delete this->reloadBar;
	delete this->hpBar;

	this->expBar = nullptr;
	this->reloadBar = nullptr;
	this->hpBar = nullptr;
	this->player = nullptr;
	this->font = nullptr;
}

///Functions

void PlayerStatusPane::update()
{
	this->reloadBar->update(this->player->getReloadPercent());

	if (this->player->wasChangedHP())
	{
		this->hpBar->update((float)this->player->getHP(), (float)this->player->getAttribute(UAT_MHP));
	}

	if (this->player->wasChangedEXP())
	{
		this->expBar->update((float)this->player->getEXP(), (float)this->player->getEXPNext());
	}

	if (this->player->wasChangedLVL())
	{
		this->lvlInfo.setString(std::to_string(this->player->getLVL()) + " lvl");
		this->lvlInfo.setOrigin(this->lvlInfo.getGlobalBounds().width, this->lvlInfo.getGlobalBounds().height / 2.f);
	}
	
	if (this->player->wasChangedAPS())
	{
		if (this->player->getAPS() == 0)
			this->apsInfo.setString("");
		else if (this->player->getAPS() == 1)
			this->apsInfo.setString(std::to_string(this->player->getAPS()) + " free attribute point");
		else
			this->apsInfo.setString(std::to_string(this->player->getAPS()) + " free attribute points");
	}
}

void PlayerStatusPane::render(sf::RenderTarget* target)
{
	this->hpBar->render(target);
	this->reloadBar->render(target);
	this->expBar->render(target);
	target->draw(this->lvlInfo);
	target->draw(this->apsInfo);
}
