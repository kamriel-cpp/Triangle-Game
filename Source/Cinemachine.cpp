//Constructors/Destructors
Cinemachine::Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
	this->smoothing = 10.f;
}

Cinemachine::~Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
	delete this->camera;
	delete this->target;
}

//Functions
void Cinemachine::setCamera (Camera* camera)
{
	this->camera = camera;
}

void Cinemachine::setTarget (sf::Shape* target)
{
	this->target = target;
}

void Cinemachine::update(const float& dt)
{
	if (this->camera != nullptr && this->target != nullptr)
	{
		if (this->camera->getView().getCenter() != this->target->getPosition())
			this->camera->move((this->target->getPosition() - this->camera->getView().getCenter()) * this->smoothing, dt);

		this->camera->move(
			(this->camera->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->camera->getWindow()), this->camera->getView())
			- this->camera->getView().getCenter()) * (this->smoothing * 0.25f), dt);
	}
}
