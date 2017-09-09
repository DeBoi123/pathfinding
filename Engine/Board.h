#pragma once
#include "Graphics.h"
#include "Player.h"
#include <vector>

class Board
{
public:
	Board(Graphics& gfx_in, Player& plr_in);
	Location GetPlayerLocation() const; //maybe I dont need the getters after all
	Location GetGoalLocation() const;
	Location GetObstacleLocation(const int i) const;
	void InitMap();
	void DrawCell(const Location& loc, const Color& c);
	void DrawSmallCell(const Location& loc, const Color& c);
	void DrawMap();
	void Draw();
	std::vector<int> GetNeighbors(int center);
	void InitNeighborhoods();
	

private:
	Graphics& gfx;
	Player& plr;
	static constexpr int cellDimension = 20;
	static constexpr int cellPadding = 2;
	static constexpr int width = 4;
	static constexpr int height = 4;
	static constexpr int nObstacles = 1;
	static constexpr Color obstacleColor = Colors::Red;
	static constexpr Color goalColor = Colors::Yellow;

	Location goalLocation = { 1,0 };
	Location obstacles[nObstacles] = {
		{ 1,1 }
	};

	int map[width*height];
	std::vector< std::vector<int> > neighborhoods;
};