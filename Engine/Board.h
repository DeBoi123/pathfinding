#pragma once
#include "Graphics.h"
#include "Player.h"
#include <vector>

class Board
{
public:
	Board(Graphics& gfx_in, Player& plr_in);

	// Getters:
	Location GetGoalLocation() const;
	std::vector<Location> GetObstacleLocation() const;
	int GetWidth() const;
	int GetHeight() const;

	//Drawing:
	void DrawCell(const Location& loc, const Color& c);
	void DrawSmallCell(const Location& loc, const Color& c);
	void Draw();

	// static const variables:
	static constexpr int cellDimension = 20;
	static constexpr int cellPadding = 2;
	static constexpr int width = 10;
	static constexpr int height = 10;
	static constexpr int offsetX = 300;
	static constexpr int offsetY = 200;
	static constexpr Color obstacleColor = Colors::Red;
	static constexpr Color goalColor = Colors::Yellow;

private:
	Graphics& gfx;
	Player& plr;

	Location goalLocation = { 4,0 };

	std::vector<Location> obstacles = { { 4,4 } };
};