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

int Location::TaxiMetric(const Location & rhs) const
{
	return (*this - rhs).TaxiNorm();
}

int TaxiMetric(const Location & lhs, const Location & rhs)
{
	return lhs.TaxiMetric(rhs);
}

int ConvertLocToInt(const Location & brdDim, const Location & loc)
{
	return loc.y * brdDim.x + loc.x;
}

Location ConvertIntToLoc(const Location & brdDim, int loc_int)
{
	int x = loc_int % brdDim.x;
	return Location(x, (x - loc_int) / brdDim.x);
}
