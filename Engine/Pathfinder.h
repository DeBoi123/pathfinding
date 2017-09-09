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

private:
	Board& brd;
	Graphics& gfx;
	std::vector<int> map;
	std::vector< std::vector<int> > neighborhoods;
};