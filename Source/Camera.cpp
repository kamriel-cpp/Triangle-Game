//Constructors/Destructors
Camera::Camera(sf::RenderWindow* window)
{
	this->view = window->getDefaultView();
	this->view.setCenter(sf::Vector2f(0.f, 0.f));
}

Camera::~Camera()
{

}

//Functions
const sf::View& Camera::getView() const
{
	return this->view;
}

const sf::Vector2f& Camera::getSize() const
{
	return this->view.getSize();
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
