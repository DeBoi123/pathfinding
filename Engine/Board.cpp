#include "Board.h"

Board::Board(Graphics & gfx_in, Player& plr_in)
	:
	gfx(gfx_in),
	plr(plr_in)
{
	plr_path = { plr.GetLocation() };
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

void Board::SetNewPlayerPath(const std::vector<Location>& path)
{
	plr_path = path;
	currentPlayerPosition = 0;
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
	DrawSmallCell(goalLocation, goalColor);
	DrawSmallCell(plr.GetLocation(), Player::playerColor);
}

void Board::MovePlayer()
{
	if (currentPlayerPosition < plr_path.size() - 1)
	{
		currentPlayerPosition++;
	}
	plr.MoveTo(plr_path.at(currentPlayerPosition));
}
