#include "Pathfinder.h"

void Pathfinder::SetBoard(const Location & brd_in, const std::vector<Location>& obst_in)
{
	boardDimensions = brd_in;
	obstacles = obst_in;
}

void Pathfinder::Initialize(const Location & plr_in, const Location & goal_in)
{
	playerLocation = plr_in;
	goalLocation = goal_in;

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
	map.clear();
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

std::vector<int> Pathfinder::GetNeighbors(const int center) const
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

std::vector<Location> Pathfinder::CrudeSearch() const
{
	int plr = playerLocation.y * boardDimensions.x + playerLocation.x;
	int goal = goalLocation.y * boardDimensions.y + goalLocation.x;
	int winningIndex = 0;
	std::vector<Location> finalPath;
	std::vector<int> finalPathInt;
	std::vector< std::vector<int> > pathList1;
	std::vector< std::vector<int> > pathList2;
	std::vector<int> currentPath;
	currentPath.clear();
	currentPath.push_back(plr);
	pathList1.push_back(currentPath);
	bool finished = (plr == goal);																		//this checks whether the player is standing on the goal already
	while (!finished)
	{
		pathList2.clear();
		for (int i = 0; i < pathList1.size(); i++)														//iterating through all currently valid paths
		{
			std::vector<int> tempPath1 = pathList1.at(i);
			int currentNode = tempPath1.at(tempPath1.size() - 1);
			for (int j = 0; j < neighborhoods.at(tempPath1.at(tempPath1.size() - 1)).size(); j++)		/*This inner loop iterates through			*/
			{																							/*all neighbors of the last location of the	*/
				int nextNode = (neighborhoods.at(currentNode)).at(j);									/*current path and extends the path by		*/
																										/*that neighbor.							*/
				if (map.at(nextNode) != 3)
				{
					std::vector<int> tempPath2 = tempPath1;
					tempPath2.push_back((neighborhoods.at(currentNode)).at(j));
					
					bool isNotLoop = true;																//check to see if a loop got created
					for (int k = 0; k < tempPath2.size() - 1; k++)
					{
						isNotLoop = isNotLoop && (tempPath2.at(tempPath2.size() - 1) != tempPath2.at(k));
					}
					if (isNotLoop)
					{
						pathList2.push_back(tempPath2);
					}
				}
			}
		}
		pathList1 = pathList2;
		pathList2.clear();
		//No path to goal:
		if (pathList1.size() == 0)
		{
			pathList1.push_back({ plr });
			winningIndex = 0;
			finished = true;
		}

		int i = 0;
		while (!finished && i < pathList1.size())
		{
			int currentPathEnd = pathList1.at(i).at(pathList1.at(i).size() - 1);
			if (currentPathEnd == goal)
			{
				winningIndex = i;
				finished = true;
			}
			i++;
		}
	}
	finalPathInt = pathList1.at(winningIndex);
	finalPath.clear();
	for (int i = 0; i < finalPathInt.size(); i++)
	{
		int x = finalPathInt.at(i) % boardDimensions.x;
		int y = (finalPathInt.at(i) - x) / boardDimensions.y;
		finalPath.push_back({ x,y });
	}

	return finalPath;
}

std::vector<Location> Pathfinder::GetCrudePath(const Location& plr_in, const Location& goal_in)
{
	Initialize(plr_in, goal_in);
	
	return CrudeSearch();
}
