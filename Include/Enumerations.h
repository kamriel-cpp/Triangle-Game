#pragma once

///Enumerations
enum RoomTags
{
	RT_NONE,
	RT_HALL_MAIN,
	RT_HALL_SECONDARY,
	RT_CORRIDOR_HORIZONTAL,
	RT_CORRIDOR_VERTICAL
};

enum Direction
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN
};

enum MovementStates
{
	MV_IDLE,
	MV_MOVING,
	MV_MOVING_LEFT,
	MV_MOVING_RIGHT,
	MV_MOVING_UP,
	MV_MOVING_DOWN
};

enum ButtonStates
{
	BTN_IDLE,
	BTN_HOVER,
	BTN_ACTIVE
};