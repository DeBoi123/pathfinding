#pragma once

class Location
{
public:
	bool operator == (Location& rhs)
	{
		return ((x == rhs.x) && (y == rhs.y));
	}
	void Add(Location& l)
	{
		x += l.x;
		y += l.y;
	}

	int x;
	int y;
};