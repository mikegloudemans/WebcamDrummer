#pragma once
#include <vector>
#include "Event_Data.h"

class Scoring
{
private:
	int currentStreak;
	int maxStreak;
	int totalNotes;
	int notesHit;
public:
	void update(std::vector<Event_Data>);
	int getScoreChange();
	int getMeterChange();
};