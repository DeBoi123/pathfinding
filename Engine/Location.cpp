#include "Location.h"
#include <cmath>

Location::Location(int x_in, int y_in)
	:
	x(x_in),
	y(y_in)
{
}

Location::Location(const Location & loc_in)
	:
	x(loc_in.x),
	y(loc_in.y)
{
}

Location Location::operator+(const Location & rhs) const
{
	return Location(x + rhs.x, y + rhs.y);
}

Location Location::operator-(const Location & rhs) const
{
	return Location(x - rhs.x, y - rhs.y);
}

Location & Location::operator+=(const Location & rhs)
{
	*this = *this + rhs;
	return *this;
}

Location & Location::operator-=(const Location & rhs)
{
	*this = *this - rhs;
	return *this;
}

int Location::TaxiNorm() const
{
	return abs(x) + abs(y);
}

int Location::TaxiMetrik(const Location & rhs) const
{
	return (*this - rhs).TaxiNorm();
}

int TaxiMetrik(const Location & lhs, const Location & rhs)
{
	return lhs.TaxiMetrik(rhs);
}
