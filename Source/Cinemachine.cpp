//Constructors/Destructors
Cinemachine::Cinemachine(Camera* camera, sf::Shape* target, sf::RenderWindow* window)
{
	this->camera = camera;
	this->target = target;
	this->window = window;
	this->smoothing = 10.f;
}

Cinemachine::~Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
	this->window = nullptr;
	delete this->camera;
	delete this->target;
	delete this->window;
}

//Functions
void Cinemachine::update(const float& dt)
{
	if (this->camera != nullptr && this->target != nullptr)
	{
		if (this->camera->getView().getCenter() != this->target->getPosition())
			this->camera->move((this->target->getPosition() - this->camera->getView().getCenter()) * this->smoothing, dt);

		this->camera->move(
			(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), this->camera->getView())
			- this->camera->getView().getCenter()) * (this->smoothing * 0.25f), dt);

		if (this->camera->getSize() != this->window->getDefaultView().getSize())
		{
			if (this->camera->getSize().x < this->window->getDefaultView().getSize().x || this->camera->getSize().y < this->window->getDefaultView().getSize().y)
				this->camera->setSize(this->camera->getSize() * (1.f + dt * 2.f));
			if (this->camera->getSize().x > this->window->getDefaultView().getSize().x || this->camera->getSize().y > this->window->getDefaultView().getSize().y)
				this->camera->setSize(this->window->getDefaultView().getSize());
		}
	}
}
