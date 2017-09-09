#include "Board.h"

Board::Board(Graphics & in_gfx)
	:
	gfx(in_gfx)
{
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
