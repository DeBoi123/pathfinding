#pragma once
#include "Location.h"
#include <vector>

class Pathfinder
{
public:
	Pathfinder(const Location& brd_in, const Location& plr_in, const Location& goal_in, const std::vector<Location>& obst_in);

	void CrudeSearch(const Location& plr_loc, const Location& goal_loc);
	void CrudePathLoc(const Location& plr_loc, const Location& goal_loc);
	std::vector<Location> GetPath() const;

private:
	//private member functions:
	void InitMap();
	void InitNeighborhoods();
	std::vector<int> GetNeighbors(int center);

	//External parameters:
	Location boardDimensions;
	Location playerLocation;
	Location goalLocation;
	std::vector<Location> obstacles;

	//Internal parameters:
	std::vector<int> map;
	std::vector< std::vector<int> > neighborhoods;
	std::vector<int> path_int;
	std::vector<Location> path_loc;
};