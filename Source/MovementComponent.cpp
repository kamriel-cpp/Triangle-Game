//Constructors/Destructors
MovementComponent::MovementComponent()
{
	this->shape = nullptr;
}

MovementComponent::~MovementComponent()
{
	this->shape = nullptr;
	delete this->shape;
}

//Functions
void MovementComponent::initVariables(sf::Shape* shape,
	float maxVelocity, float acceleration, float deceleration)
{
	this->shape = shape;
	this->maxVelocity = maxVelocity;
	this->acceleration = acceleration;
	this->deceleration = deceleration;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		return this->velocity.x == 0.f && this->velocity.y == 0.f ? true : false;
	    break;
	case MOVING:
		return this->velocity.x != 0.f || this->velocity.y != 0.f ? true : false;
	    break;
	case MOVING_LEFT:
		return this->velocity.x < 0.f ? true : false;
	    break;
	case MOVING_RIGHT:
		return this->velocity.x > 0.f ? true : false;
	    break;
	case MOVING_UP:
		return this->velocity.y < 0.f ? true : false;
	    break;
	case MOVING_DOWN:
		return this->velocity.y > 0.f ? true : false;
	    break;
	}
	return false;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Acceleration a shape until it reaches the max velocity*/
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	/*Decelerates the shape and controls the max velocity*/
	if (this->velocity.x > 0.f)			//Check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;
		//Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f)	//Check for negative x
	{
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;
		//Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f)			//Check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;
		//Deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f)	//Check for negative y
	{
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;
		//Deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	//Final move
	this->shape->move(this->velocity * dt);
}
