#pragma once

//General includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <map>
#include <cmath>

//SFML includes
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//I'm not really sure where this part should be...
//maybe I'll put it in a separate header
enum RoomTags { NONE, FRONT, BACK, MAIN, SECONDARY, CORRIDOR_HORIZONTAL, CORRIDOR_VERTICAL };
enum Direction { LEFT, RIGHT, UP, DOWN };
enum MovementStates { IDLE, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };
