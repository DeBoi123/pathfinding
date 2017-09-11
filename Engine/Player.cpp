#include "Player.h"

Player::Player(Location & loc_in, Pathfinder& pfnd_in)
	:
	loc(loc_in),
	pfnd(pfnd_in)
{
}

Location Player::GetLocation()
{
	return loc;
}

void Player::MoveOneStepTo(const Location& newLoc)
{
	SetNewPath(newLoc);
	if (path.size() > 1)
	{
		loc = path.at(1);
	}
	else
	{
		loc = path.at(0);
	}
	
}

void Player::SetNewPath(const Location& goalLoc)
{
	path = pfnd.GetCrudePath(loc, goalLoc);
}
