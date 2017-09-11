#pragma once
#include "Location.h"
#include <vector>

class Pathfinder
{
public:

	void SetBoard(const Location& brd_in, const std::vector<Location>& obst_in);
	std::vector<Location> GetCrudePath(const Location& plr_in, const Location& goal_in);

private:
	//private member functions:
	void Initialize(const Location& plr_in, const Location& goal_in);
	void InitMap();
	void InitNeighborhoods();
	std::vector<int> GetNeighbors(const int center) const;

	std::vector<Location> CrudeSearch() const;

	//External parameters:
	Location boardDimensions;
	Location playerLocation;
	Location goalLocation;
	std::vector<Location> obstacles;

	//Internal parameters:
	std::vector<int> map;
	std::vector< std::vector<int> > neighborhoods;
};