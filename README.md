# pathfinding
first attempt on implementing an A* search algorithm

The first implementation is not actually an A* algorithm, but rather a very crude pathfinding algorithm which doesnt
take any heuristics into account.
Starting at the player location all possible (i.e. nonobstructed) paths are extended until one of them reaches the goal location.
This however is still a very slow process for complicated setups of obstacles.
I will not try to fix that, rather I'll focus on laying the foundations to implementing A* proper.
