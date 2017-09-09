#include "Pathfinder.h"

Pathfinder::Pathfinder(Board & brd_in, Graphics & gfx_in)
	:
	brd(brd_in),
	gfx(gfx_in)
{
	InitMap();
	InitNeighborhoods();
}

void Pathfinder::InitMap()
{
	int plrLoc = brd.GetPlayerLocation().y * Board::width + brd.GetPlayerLocation().x;
	int goalLoc = brd.GetGoalLocation().y * Board::width + brd.GetGoalLocation().x;
	int obstacleLoc[Board::nObstacles];
	for (int i = 0; i < Board::nObstacles; i++)
	{
		obstacleLoc[i] = brd.GetObstacleLocation(i).y * Board::width + brd.GetObstacleLocation(i).x;
	}

	for (int i = 0; i < Board::width * Board::height; i++)
	{
		bool isNotObstacle = true;

		for (int j = 0; j < Board::nObstacles; j++)
		{
			isNotObstacle = isNotObstacle && (i != obstacleLoc[j]);
		}

		if (!isNotObstacle)
		{
			map.push_back(3);
		}
		else if (i == goalLoc)
		{
			map.push_back(2);
		}
		else if (i == plrLoc)
		{
			map.push_back(1);
		}
		else
		{
			map.push_back(0);
		}
	}
}

void Pathfinder::DrawMap()
{
	for (int i = 0; i < Board::width * Board::height; i++)
	{
		if (map.at(i) == 3)
		{
			gfx.PutPixel(i % Board::width, (i - (i % Board::width)) / Board::width, Board::obstacleColor);
		}
		else if (map.at(i) == 2)
		{
			gfx.PutPixel(i % Board::width, (i - (i % Board::width)) / Board::width, Board::goalColor);
		}
		else if (map.at(i) == 1)
		{
			gfx.PutPixel(i % Board::width, (i - (i % Board::width)) / Board::width, Player::playerColor);
		}
		else
		{
			gfx.PutPixel(i % Board::width, (i - (i % Board::width)) / Board::width, Colors::Black);
		}
	}
}

std::vector<int> Pathfinder::GetNeighbors(int center)
{
	std::vector<int> neighbors;
	//check for left neighbor and add if it exists
	if (center % Board::width != 0)
	{
		neighbors.push_back(center - 1);
	}
	//right
	if (center % Board::width != Board::width - 1)
	{
		neighbors.push_back(center + 1);
	}
	// top
	if (center >= Board::width)
	{
		neighbors.push_back(center - Board::width);
	}
	// bottom
	if (center < Board::height*(Board::width - 1))
	{
		neighbors.push_back(center + Board::width);
	}

	return neighbors;
}

void Pathfinder::InitNeighborhoods()
{
	for (int i = 0; i < Board::width * Board::height; i++)
	{
		neighborhoods.push_back(GetNeighbors(i));
	}
}
