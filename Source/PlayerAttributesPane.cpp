///Initializations
void PlayerAttributesPane::initStatsInfo(sf::Font* font, sf::View* view)
{
	for (int i = 0; i < 7; i++)
	{
		this->statsInfo["UI_STINF_" + std::to_string(i)] = new sf::Text("TXT", *font, 20);
		this->statsInfo["UI_STINF_" + std::to_string(i)]->setPosition(sf::Vector2f(
			-view->getSize().x / 2 + 40.f + i * 100.f,
			view->getSize().y / 2 - 50.f));
	}
}

void PlayerAttributesPane::initButtons(sf::Font* font, sf::View* view)
{
	for (int i = 0; i < 7; i++)
	{
		std::string text;

		switch (i)
		{
		case UAT_MHP:
			text = "MHP";
			break;
		case UAT_SPS:
			text = "SPS";
			break;
		case UAT_SPR:
			text = "SPR";
			break;
		case UAT_DMG:
			text = "DMG";
			break;
		case UAT_BPS:
			text = "BPS";
			break;
		case UAT_BSP:
			text = "BSP";
			break;
		case UAT_BRD:
			text = "BRD";
			break;
		default:
			text = "WTF";
			break;
		}

		this->buttons["UI_BTN_" + std::to_string(i)] = new Button(
			-view->getSize().x / 2 + 27.5f + i * 100.f, view->getSize().y / 2 - 37.5f,
			-2.f, -15.5f, 20.f, 20.f,
			font, "+", text, 25,
			{ 250, 250, 250, 200 }, { 250, 250, 250, 250 }, {  50, 250,  50, 200 },
			{ 250, 250, 250,  25 }, { 250, 250, 250,  50 }, { 250, 250, 250,  13 },
			{ 250, 250, 250, 200 }, { 250, 250, 250, 250 }, {  50, 250,  50, 200 }, 1);
	}
}

///Constructors/Destructors
PlayerAttributesPane::PlayerAttributesPane(sf::Font* font, sf::View* view,
	sf::Vector2f* mouse_pos_view, Player* player)
	: mousePosView(mouse_pos_view), player(player)
{
	this->initStatsInfo(font, view);
	this->initButtons(font, view);
}

PlayerAttributesPane::~PlayerAttributesPane()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
		delete it->second;

	for (auto it = this->statsInfo.begin(); it != this->statsInfo.end(); ++it)
		delete it->second;

	this->mousePosView = nullptr;
	this->player = nullptr;
}

///Functions
void PlayerAttributesPane::updateStatsInfo()
{
	for (int i = 0; i < 7; i++)
	{
		std::string text;

		switch (i)
		{
		case UAT_MHP:
			text = "MHP";
			break;
		case UAT_SPS:
			text = "SPS";
			break;
		case UAT_SPR:
			text = "SPR";
			break;
		case UAT_DMG:
			text = "DMG";
			break;
		case UAT_BPS:
			text = "BPS";
			break;
		case UAT_BSP:
			text = "BSP";
			break;
		case UAT_BRD:
			text = "BRD";
			break;
		default:
			text = "WTF";
			break;
		}

		text += "  ";
		text += std::to_string(this->player->getAttribute(i));

		this->statsInfo["UI_STINF_" + std::to_string(i)]->setString(text);
	}
}

void PlayerAttributesPane::updateButtons()
{
	for (auto &it : this->buttons)
		it.second->update(*this->mousePosView);

	for (int i = 0; i < 7; i++)
	{
		if (this->buttons["UI_BTN_" + std::to_string(i)]->isPressed())
		{
			if (!this->buttons["UI_BTN_" + std::to_string(i)]->wasPressed)
			{
				this->buttons["UI_BTN_" + std::to_string(i)]->wasPressed = true;
				this->player->manualDistributeAPS(i);
			}
		}
		else
		{
			this->buttons["UI_BTN_" + std::to_string(i)]->wasPressed = false;
		}
	}
}

void PlayerAttributesPane::update()
{
	this->updateStatsInfo();

	if (this->player->getAPS())
		this->updateButtons();
}

void PlayerAttributesPane::render(sf::RenderTarget* target)
{
	if (this->player->getAPS())
		for (auto &it : this->buttons)
			it.second->render(target);

	for (int i = 0; i < 7; i++)
		target->draw(*this->statsInfo["UI_STINF_" + std::to_string(i)]);
}
