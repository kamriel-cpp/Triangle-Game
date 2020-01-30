#pragma once

///Enumerations
enum RoomTags
{
	RT_NONE = 0,
	RT_HALL_MAIN,
	RT_HALL_SECONDARY,
	RT_CORRIDOR_HORIZONTAL,
	RT_CORRIDOR_VERTICAL
};

enum Direction
{
	DIR_LEFT = 0,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};

enum MovementStates
{
	MV_IDLE = 0,
	MV_MOVING,
	MV_MOVING_LEFT,
	MV_MOVING_RIGHT,
	MV_MOVING_UP,
	MV_MOVING_DOWN
};

enum ButtonStates
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};
