#pragma once
#include "Graphics.h"
#include "Player.h"

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

private:
	Graphics& gfx;
	Player& plr;
	static constexpr int cellDimension = 20;
	static constexpr int cellPadding = 2;
	static constexpr int width = 40;
	static constexpr int height = 30;
	static constexpr int nObstacles = 3;
	static constexpr Color obstacleColor = Colors::Red;
	static constexpr Color goalColor = Colors::Yellow;

	Location goalLocation = { 20,10 };
	Location obstacles[nObstacles] = {
		{ 10,10 },
		{ 20,20 },
		{ 30,10 }
	};

	int map[width*height];
};