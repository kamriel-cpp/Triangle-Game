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

sf::View& Camera::getView()
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

void Camera::move(unsigned int direction)
{
	if (direction == LEFT)
		this->view.move(-1000.f * this->dt, 0);
	else if (direction == RIGHT)
		this->view.move(1000.f * this->dt, 0);
	else if (direction == UP)
		this->view.move(0, -1000.f * this->dt);
	else if (direction == DOWN)
		this->view.move(0, 1000.f * this->dt);
}

void Camera::zoom(unsigned int direction)
{
	if (direction == IN)
		this->view.zoom(1.01f);
	else if (direction == OUT)
		this->view.zoom(0.99f);
}

void Camera::zoom(float factor)
{
	this->view.zoom(factor);
}

void Camera::update(const float& dt)
{
	this->dt = dt;
}

void Camera::updateView()
{
	this->window->setView(this->view);
}
