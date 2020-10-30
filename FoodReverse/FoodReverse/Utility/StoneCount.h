#ifndef STONE_COUNT_H
#define STONE_COUNT_H

struct StoneCount
{
	StoneCount(int black = 0, int white = 0) : black_(black), white_(white) {}

	int black_;
	int white_;
};

#endif
