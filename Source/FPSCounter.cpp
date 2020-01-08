//Constructors/Destructors
FPSCounter::FPSCounter(const sf::Vector2f& position, const sf::Font& font)
{
    this->fps = 0.f;
    this->frameCount = 0;

    this->text.setFont(font);
    this->text.setPosition(position);
    this->text.setCharacterSize(30);
}

//Functions
void FPSCounter::update()
{
    this->frameCount++;

    if (this->delayTimer.getElapsedTime().asSeconds() > 0.2f)
    {
        this->fps = this->frameCount / this->fpsTimer.restart().asSeconds();
        this->frameCount = 0;
        this->delayTimer.restart();
    }

    this->text.setString("FPS " + std::to_string((int)fps));
}

void FPSCounter::render(sf::RenderTarget* target)
{
    target->draw(this->text);
}
