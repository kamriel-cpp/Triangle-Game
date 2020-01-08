#pragma once

///Enums
enum RoomTags { NONE, FRONT, BACK, MAIN, SECONDARY, CORRIDOR_HORIZONTAL, CORRIDOR_VERTICAL };
enum Direction { LEFT, RIGHT, UP, DOWN };
enum MovementStates { IDLE, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
enum ButtonStates { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };

///Debug bools
static bool debugMode = true;
static bool debugShowFPSCounter = true;
static bool debugConsoleOutput = true;
static bool debugShowCollisionCheckers = false;
static bool debugCollisionsWithEnemies = true;
