///Constructors/Destructors
Camera::Camera(sf::View* view, sf::Shape* target, sf::RenderWindow* window)
{
	this->view = view;
	this->target = target;
	this->window = window;
	this->smoothing = 10.f;
}

Camera::~Camera()
{
	this->window = nullptr;
	this->target = nullptr;
	this->view = nullptr;
}

///Functions
void Camera::update(const float& dt)
{
	if (this->view != nullptr && this->target != nullptr)
	{
		if (this->view->getCenter() != this->target->getPosition())
			this->view->move(((this->target->getPosition() - this->view->getCenter()) * this->smoothing) * dt);

		this->view->move(
			((this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window), *this->view)
			- this->view->getCenter()) * (this->smoothing * 0.25f)) * dt);

		///FUTURE FEATURE zooming effect at the start of the game
		//if (this->view->getSize() != this->window->getDefaultView().getSize())
		//{
		//	if (this->view->getSize().x < this->window->getDefaultView().getSize().x || this->view->getSize().y < this->window->getDefaultView().getSize().y)
		//		this->view->setSize(this->view->getSize() * (1.f + dt * 2.f));
		//	if (this->view->getSize().x > this->window->getDefaultView().getSize().x || this->view->getSize().y > this->window->getDefaultView().getSize().y)
		//		this->view->setSize(this->window->getDefaultView().getSize());
		//}
	}
}
