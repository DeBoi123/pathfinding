#pragma once
#include "Location.h"
#include "Colors.h"

class Obstacle
{
public:
	Obstacle(Location& loc_in);

private:
	Location loc;
	static constexpr Color c = Colors::Red;
};