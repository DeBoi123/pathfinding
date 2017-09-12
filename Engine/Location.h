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
	bool operator != (Location& rhs)
	{
		return ((x != rhs.x) || (y != rhs.y));
	}

	//other member functions:
	int TaxiNorm() const;
	int TaxiMetric(const Location& rhs) const;


	//Data members:
	int x;
	int y;
};

int TaxiMetric(const Location& lhs, const Location& rhs);

int ConvertLocToInt(const Location& brdDim, const Location& loc);
Location ConvertIntToLoc(const Location& brdDim, int loc_int);