#pragma once

///Enumerations
enum RoomsTags
{
	RT_NONE = 0,
	RT_HALL_MAIN,
	RT_HALL_SECONDARY,
	RT_CORRIDOR_HORIZONTAL,
	RT_CORRIDOR_VERTICAL
};

enum Directions
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

enum InfoTypes
{
	IT_VALUE = 0,
	IT_PERCENT
};

enum UnitAttributesTags
{
	UAT_MHP = 0,		///Maximum HitPoints
	UAT_SPS,			///Shoots Per Second (equal 1 / reload time)
	UAT_SPR,			///SPRead
	UAT_DMG,			///DaMaGe
	UAT_BPS,			///Bullets Per Shoot
	UAT_BSP,			///Bullet SPeed
	UAT_BRD				///Bullet RaDius
};
