#include "Board.h"

Board::Board(Graphics & gfx_in, Player& plr_in)
	:
	gfx(gfx_in),
	plr(plr_in)
{
}

Location Board::GetGoalLocation() const
{
	return goalLocation;
}

std::vector<Location> Board::GetObstacleLocation() const
{

	return obstacles;
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

bool Board::GoalSet() const
{
	return goalSet;
}

bool Board::ObstaclesSet() const
{
	return obstaclesSet;
}

void Board::AddNewObstacle(const int x, const int y)
{
	if ((x >= offsetX) && x < (width * cellDimension + offsetX) && (y >= offsetY) && (y < height * cellDimension + offsetY))
	{
		int tempX = x - offsetX;
		int tempY = y - offsetY;
		Location newLoc = { ( tempX - ( tempX % cellDimension ) ) / cellDimension, (tempY - (tempY % cellDimension)) / cellDimension };
		bool isNewObstacle = true;
		for (int i = 0; i < obstacles.size(); i++)
		{
			isNewObstacle = isNewObstacle && (newLoc != obstacles.at(i));
		}
		if (isNewObstacle)
		{
			obstacles.push_back(newLoc);
		}
	}
}

void Board::DeleteObstacles()
{
	obstacles.clear();
	obstaclesSet = false;
}

void Board::DeleteGoal()
{
	goalSet = false;
}

void Board::SetObstacles(bool b)
{
	obstaclesSet = b;
}

void Board::SetGoal(const int x, const int y)
{
	if ((x >= offsetX) && x < (width * cellDimension + offsetX) && (y >= offsetY) && (y < height * cellDimension + offsetY))
	{
		int tempX = x - offsetX;
		int tempY = y - offsetY;
		goalLocation = { (tempX - (tempX % cellDimension)) / cellDimension, (tempY - (tempY % cellDimension)) / cellDimension };
		goalSet = true;
	}
}

void Board::DrawCell(const Location & loc, const Color& c)
{
	for (int y = 0; y < cellDimension; y++)
	{
		for (int x = 0; x < cellDimension; x++)
		{
			gfx.PutPixel( loc.x * cellDimension + x + offsetX, loc.y * cellDimension + y + offsetY, c );
		}
	}
}

void Board::DrawSmallCell(const Location & loc, const Color & c)
{
	for (int y = cellPadding; y < cellDimension - cellPadding; y++)
	{
		for (int x = cellPadding; x < cellDimension - cellPadding; x++)
		{
			gfx.PutPixel(loc.x * cellDimension + x + offsetX, loc.y * cellDimension + y + offsetY, c);
		}
	}
}

void Board::Draw()
{
	for (int y = 0; y < height * cellDimension; y++)
	{
		for (int x = 0; x < width * cellDimension; x++)
		{
			gfx.PutPixel(x + offsetX, y + offsetY, Colors::Gray);
		}
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			DrawSmallCell(Location(x, y), Colors::Black);
		}
	}

	for (int i = 0; i < obstacles.size(); i++)
	{
		DrawSmallCell(obstacles.at(i), obstacleColor);
	}
	if (goalSet)
	{
		DrawSmallCell(goalLocation, goalColor);
	}
	DrawSmallCell(plr.GetLocation(), Player::playerColor);
}