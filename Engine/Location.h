#pragma once

class Location
{
public:
	//Constructors:
	Location() = default;
	Location(int x_in, int y_in);
	Location(const Location& loc_in);

	//Operators:
	Location operator+(const Location& rhs) const;
	Location operator-(const Location& rhs) const;
	Location& operator+=(const Location& rhs);
	Location& operator-=(const Location& rhs);

	bool operator == (Location& rhs)
	{
		return ((x == rhs.x) && (y == rhs.y));
	}

	//other member functions:
	int TaxiNorm() const;
	int TaxiMetrik(const Location& rhs) const;


	//Data members:
	int x;
	int y;
};