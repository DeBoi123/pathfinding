#pragma once
#include "Location.h"
#include "Colors.h"

class Player
{
public:
	Player(Location& loc_in);
	Location GetLocation();
	void MoveTo(const Location& newLoc);
	static constexpr Color playerColor = Colors::Green;

private:

	Location loc;
};