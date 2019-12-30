//Constructors/Destructors
Cinemachine::Cinemachine()
{
	this->camera = nullptr;
	this->target = nullptr;
	this->damping = 0.f;
	this->deadZone.x = 0.f;
	this->deadZone.y = 0.f;
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

void Cinemachine::setDamping(float damping)
{
	if (damping < 0.f)
		this->damping = 0.f;
	else if (damping > 10.f)
		this->damping = 10.f;
	else
		this->damping = damping;
}

void Cinemachine::setDeadZone(const sf::Vector2f& dead_zone)
{
	//X axis
	if (deadZone.x < -1.f)
		this->deadZone.x = -1.f;
	else if (deadZone.x > 1.f)
		this->deadZone.x = 1.f;
	else
		this->deadZone.x = deadZone.x;

	//Y axis
	if (deadZone.y < -1.f)
		this->deadZone.y = -1.f;
	else if (deadZone.y > 1.f)
		this->deadZone.y = 1.f;
	else
		this->deadZone.y = deadZone.y;
}

void Cinemachine::setDeadZone(float dead_zone_x, float dead_zone_y)
{
	//X axis
	if (dead_zone_x < -1.f)
		this->deadZone.x = -1.f;
	else if (deadZone.x > 1.f)
		this->deadZone.x = 1.f;
	else
		this->deadZone.x = dead_zone_x;

	//Y axis
	if (dead_zone_y < -1.f)
		this->deadZone.y = -1.f;
	else if (dead_zone_y > 1.f)
		this->deadZone.y = 1.f;
	else
		this->deadZone.y = dead_zone_y;
}

void Cinemachine::update(const float& dt)
{
	if (this->camera != nullptr && this->target != nullptr)
	{
		/*if (this->camera->getView().getCenter().x
			+ (this->camera->getView().getSize().x * this->deadZone.x) * 0.5f
			< this->target->getPosition().x)
		{
			this->camera->move((this->target->getPosition().x
				- this->camera->getView().getCenter().x) * (1.f + this->damping), 0.f, dt);
		}
		else if (this->camera->getView().getCenter().x
			- (this->camera->getView().getSize().x * this->deadZone.x) * 0.5f
			> this->target->getPosition().x)
		{
			this->camera->move((this->target->getPosition().x
				- this->camera->getView().getCenter().x) * (1.f + this->damping), 0.f, dt);
		}

		if (this->camera->getView().getCenter().y
			+ (this->camera->getView().getSize().y * this->deadZone.x) * 0.5f
			< this->target->getPosition().y)
		{
			this->camera->move(0.f, (this->target->getPosition().y
				- this->camera->getView().getCenter().y) * (1.f + this->damping), dt);
		}
		else if (this->camera->getView().getCenter().y
			- (this->camera->getView().getSize().y * this->deadZone.x) * 0.5f
			> this->target->getPosition().y)
		{
			this->camera->move(0.f, (this->target->getPosition().y
				- this->camera->getView().getCenter().y) * (1.f + this->damping), dt);
		}*/
		if (this->camera->getView().getCenter().x
			+ (this->camera->getView().getSize().x * this->deadZone.x) * 0.5f
			< this->target->getPosition().x)
		{
			this->camera->move((this->target->getPosition().x
				- this->camera->getView().getCenter().x) * (1.f + this->damping), 0.f, dt);
		}
		else if (this->camera->getView().getCenter().x
			- (this->camera->getView().getSize().x * this->deadZone.x) * 0.5f
			> this->target->getPosition().x)
		{
			this->camera->move((this->target->getPosition().x
				- this->camera->getView().getCenter().x) * (1.f + this->damping), 0.f, dt);
		}

		if (this->camera->getView().getCenter().y
			+ (this->camera->getView().getSize().y * this->deadZone.x) * 0.5f
			< this->target->getPosition().y)
		{
			this->camera->move(0.f, (this->target->getPosition().y
				- this->camera->getView().getCenter().y) * (1.f + this->damping), dt);
		}
		else if (this->camera->getView().getCenter().y
			- (this->camera->getView().getSize().y * this->deadZone.x) * 0.5f
			> this->target->getPosition().y)
		{
			this->camera->move(0.f, (this->target->getPosition().y
				- this->camera->getView().getCenter().y) * (1.f + this->damping), dt);
		}

		if (this->camera->getView().getCenter().x
			+ (this->camera->getView().getSize().x * 0.19f) * 0.5f
			> this->target->getPosition().x
			&& this->camera->getView().getCenter().x
			- (this->camera->getView().getSize().x * 0.19f) * 0.5f
			< this->target->getPosition().x
			&& this->camera->getView().getCenter().y
			+ (this->camera->getView().getSize().y * 0.19f) * 0.5f
			> this->target->getPosition().y
			&& this->camera->getView().getCenter().y
			- (this->camera->getView().getSize().y * 0.19f) * 0.5f
			< this->target->getPosition().y)
		{
			this->camera->move(
				(this->camera->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->camera->getWindow()), this->camera->getView()).x
					- this->camera->getView().getCenter().x) * 1.f,
				(this->camera->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->camera->getWindow()), this->camera->getView()).y
					- this->camera->getView().getCenter().y) * 1.f, dt);
		}
		/*this->camera->move(
			(this->camera->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->camera->getWindow()), this->camera->getView()).x
				- this->camera->getView().getCenter().x) * 0.1f,
			(this->camera->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->camera->getWindow()), this->camera->getView()).y
				- this->camera->getView().getCenter().y) * 0.1f, dt);*/
	}
}
