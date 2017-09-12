#pragma once
#include <vector>
#include "Location.h"

class Node
{
public:

	int f;
	int g;
	int h;
	bool closed;
	int content;

	Location loc;
	Node& parent;
	std::vector<Node&> neighbors;
};