#pragma once
#include "Board.h"

class Pathfinder
{
public:
	Pathfinder(Board& brd_in, Graphics& gfx_in);
	void InitMap();
	void DrawMap();
	std::vector<int> GetNeighbors(int center);
	void InitNeighborhoods();
	void CrudeSearch(const Location& plr_loc, const Location& goal_loc);
	void CrudePathLoc(const Location& plr_loc, const Location& goal_loc);
	std::vector<Location> GetPath() const;

private:
	Board& brd;
	Graphics& gfx;
	std::vector<int> map;
	std::vector< std::vector<int> > neighborhoods;
	std::vector<int> path_int;
	std::vector<Location> path_loc;
};