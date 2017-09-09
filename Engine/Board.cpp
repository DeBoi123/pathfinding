#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx_in, Player& plr_in)
	:
	gfx(gfx_in),
	plr(plr_in)
{
	InitMap();
}

Location Board::GetPlayerLocation() const
{
	return plr.GetLocation();
}

Location Board::GetGoalLocation() const
{
	return goalLocation;
}

Location Board::GetObstacleLocation(const int i) const
{
	assert (i < nObstacles);
	return obstacles[i];
}

void Board::InitMap()
{
	int playerLoc = plr.GetLocation().y * width + plr.GetLocation().x;
	int goalLoc = goalLocation.y * width + goalLocation.x;
	int obstacleLoc[nObstacles];
	for (int i = 0; i < nObstacles; i++)
	{
		obstacleLoc[i] = obstacles[i].y * width + obstacles[i].x;
	}

	for (int i = 0; i < width*height; i++)
	{
		bool isNotObstacle = true;

		for (int j = 0; j < nObstacles; j++)
		{
			isNotObstacle = isNotObstacle && (i != obstacleLoc[j]);
		}

		if (!isNotObstacle)
		{
			map[i] = 3;
		}
		else if (i == goalLoc)
		{
			map[i] = 2;
		}
		else if (i == playerLoc)
		{
			map[i] = 1;
		}
		else
		{
			map[i] = 0;
		}
	}
}

void Board::DrawCell(const Location & loc, const Color& c)
{
	for (int y = 0; y < cellDimension; y++)
	{
		for (int x = 0; x < cellDimension; x++)
		{
			gfx.PutPixel( loc.x * cellDimension + x,loc.y * cellDimension + y,c );
		}
	}
}

void Board::DrawSmallCell(const Location & loc, const Color & c)
{
	for (int y = cellPadding; y < cellDimension - cellPadding; y++)
	{
		for (int x = cellPadding; x < cellDimension - cellPadding; x++)
		{
			gfx.PutPixel(loc.x * cellDimension + x, loc.y * cellDimension + y, c);
		}
	}
}

void Board::DrawMap()
{

	for (int i = 0; i < width*height; i++)
	{
		if (map[i] == 3)
		{
			gfx.PutPixel(i % width, (i - (i % width)) / width, obstacleColor);
		}
		else if (map[i] == 2)
		{
			gfx.PutPixel(i % width, (i - (i % width)) / width, goalColor);
		}
		else if (map[i] == 1)
		{
			gfx.PutPixel(i % width, (i - (i % width)) / width, Player::playerColor);
		}
		else
		{
			gfx.PutPixel(i % width, (i - (i % width)) / width, Colors::Black);
		}
	}
}

void Board::Draw()
{
	for (int i = 0; i < nObstacles; i++)
	{
		DrawCell(obstacles[i], obstacleColor);
	}
	DrawSmallCell(goalLocation, goalColor);
	DrawSmallCell(plr.GetLocation(), Player::playerColor);
}
