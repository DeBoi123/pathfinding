#include "Player.h"

Player::Player(Location & loc_in)
	:
	loc(loc_in)
{
}

Location Player::GetLocation()
{
	return loc;
}
