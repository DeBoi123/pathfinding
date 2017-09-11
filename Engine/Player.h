#pragma once
#include "Location.h"
#include "Colors.h"
#include "Pathfinder.h"

class Player
{
public:
	Player(Location& loc_in, Pathfinder& pfnd_in);

	//Getters:
	Location GetLocation();

	void MoveOneStepTo(const Location& newLoc);
	static constexpr Color playerColor = Colors::Green;

private:

	void SetNewPath(const Location& goalLoc);


	Pathfinder & pfnd;
	std::vector<Location> path;
	Location loc;
};