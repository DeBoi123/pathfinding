#pragma once

class Location
{
public:
	void Add(Location& l);

	bool operator == (Location& rhs)
	{
		return ((x == rhs.x) && (y == rhs.y));
	}

	int x;
	int y;
};