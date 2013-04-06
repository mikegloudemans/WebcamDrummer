#pragma once
#include <vector>
#include "Event_Data.h"

class Scoring
{
private:
public:
	void update(std::vector<Event_Data>);
	int getScoreChange();
	int getMeterChange();
};