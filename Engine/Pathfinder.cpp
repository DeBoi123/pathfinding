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

void Pathfinder::CrudeSearch(const Location & plr_loc, const Location & goal_loc)
{
	int plr = plr_loc.y * Board::width + plr_loc.x;
	int goal = goal_loc.y * Board::width + goal_loc.x;
	std::vector< std::vector<int> > pathList1;
	std::vector< std::vector<int> > pathList2;
	std::vector<int> currentPath;
	currentPath.push_back(plr);
	pathList1.push_back(currentPath);
	bool finished = false;

	while (!finished)
	{
		pathList2.clear();
		for (int i = 0; i < pathList1.size(); i++) //iterating through all currently valid paths
		{
			std::vector<int> tempPath1 = pathList1.at(i);
			for (int j = 0; j < neighborhoods.at(tempPath1.at(tempPath1.size() - 1)).size(); j++)
				/*
				This inner loop iterates through all neighbors of the last location of the current path and extends the path by that neighbor.
				*/
			{
				int currentNode = tempPath1.at(tempPath1.size() - 1);
				int nextNode = (neighborhoods.at(currentNode)).at(j);

				if (map.at(nextNode) != 3)
				{
					std::vector<int> tempPath2 = tempPath1;
					tempPath2.push_back((neighborhoods.at(currentNode)).at(j));
					pathList2.push_back(tempPath2);
				}
			}
		}
		pathList1 = pathList2;
		pathList2.clear();
		int i = 0;
		while (!finished && i < pathList1.size())
		{
			int currentPathEnd = pathList1.at(i).at(pathList1.at(i).size() - 1);
			if (currentPathEnd == goal)
			{
				path_int = pathList1.at(i);
				finished = true;
			}
			i++;
		}
	}
}

void Pathfinder::CrudePathLoc(const Location & plr_loc, const Location & goal_loc)
{
	CrudeSearch(plr_loc, goal_loc);
	path_loc.clear();
	for (int i = 0; i < path_int.size(); i++)
	{
		int x = path_int.at(i) % Board::width;
		int y = (path_int.at(i) - x) / Board::width;
		path_loc.push_back({ x,y });
	}
}

std::vector<Location> Pathfinder::GetPath() const
{
	return path_loc;
}
