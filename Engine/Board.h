#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, const Color& c);
	void DrawSmallCell(const Location& loc, const Color& c);

private:
	Graphics& gfx;
	static constexpr int cellDimension = 20;
	static constexpr int cellPadding = 2;
	static constexpr int width = 40;
	static constexpr int height = 30;
};