//Constructors/Destructors
Camera::Camera()
{
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	this->view.setCenter(sf::Vector2f(
		window_bounds.width / 2.f,
		window_bounds.height / 2.f));
	this->view.setSize(sf::Vector2f(
		window_bounds.width / 2.f,
		window_bounds.height / 2.f));
}

Camera::~Camera()
{
	this->window = nullptr;
	delete this->window;
}

//Functions
const sf::View& Camera::getView() const
{
	return this->view;
}

void Camera::setWindow(sf::RenderWindow* window)
{
	this->window = window;
}

void Camera::setSize(const sf::Vector2f& size)
{
	this->view.setSize(size);
}

void Camera::setCenter(const sf::Vector2f& center)
{
	this->view.setCenter(center);
}

void Camera::setViewport(const sf::FloatRect& viewport)
{
	this->view.setViewport(viewport);
}

void Camera::move(float offsetX, float offsetY, const float& dt)
{
	this->view.move(offsetX * dt, offsetY * dt);
}

void Camera::move(const sf::Vector2f offset, const float& dt)
{
	this->view.move(offset * dt);
}

void Camera::zoom(const float factor)
{
	this->view.zoom(factor);
}
