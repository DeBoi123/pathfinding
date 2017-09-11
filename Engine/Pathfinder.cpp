#include "Pathfinder.h"

Pathfinder::Pathfinder(const Location& brd_in, const Location& plr_in, const Location& goal_in, const std::vector<Location>& obst_in)
	:
	boardDimensions(brd_in),
	playerLocation(plr_in),
	goalLocation(goal_in),
	obstacles(obst_in)
{
	InitMap();
	InitNeighborhoods();
}

void Pathfinder::InitMap()
{
	int width = boardDimensions.x;
	int height = boardDimensions.y;
	int plrLoc = playerLocation.y * width + playerLocation.x;
	int goalLoc = goalLocation.y * width + goalLocation.x;
	std::vector<int> obstacleLoc;
	for (int i = 0; i < obstacles.size(); i++)
	{
		obstacleLoc.push_back( obstacles.at(i).y * width + obstacles.at(i).x);
	}

	for (int i = 0; i < width * height; i++)
	{
		bool isNotObstacle = true;

		for (int j = 0; j < obstacles.size(); j++)
		{
			isNotObstacle = isNotObstacle && (i != obstacleLoc.at(j));
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

std::vector<int> Pathfinder::GetNeighbors(int center)
{
	int width = boardDimensions.x;
	int height = boardDimensions.y;
	std::vector<int> neighbors;
	//check for left neighbor and add if it exists
	if (center % width != 0)
	{
		neighbors.push_back(center - 1);
	}
	//right
	if (center % width != width - 1)
	{
		neighbors.push_back(center + 1);
	}
	// top
	if (center >= width)
	{
		neighbors.push_back(center - width);
	}
	// bottom
	if (center < height * (width - 1))
	{
		neighbors.push_back(center + width);
	}

	return neighbors;
}

void Pathfinder::InitNeighborhoods()
{
	for (int i = 0; i < boardDimensions.x * boardDimensions.y; i++)
	{
		neighborhoods.push_back(GetNeighbors(i));
	}
}

void Pathfinder::CrudeSearch(const Location & plr_loc, const Location & goal_loc)
{
	int plr = plr_loc.y * boardDimensions.x + plr_loc.x;
	int goal = goal_loc.y * boardDimensions.y + goal_loc.x;
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
		int x = path_int.at(i) % boardDimensions.x;
		int y = (path_int.at(i) - x) / boardDimensions.y;
		path_loc.push_back({ x,y });
	}
}

std::vector<Location> Pathfinder::GetPath() const
{
	return path_loc;
}
