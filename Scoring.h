#pragma once
#include <vector>
#include "Event_Data.h"

class Scoring
{
private:

	static const int pointsPerNote = 200;
	static const int badHitPenalty = 50;		// Penalty for hitting at wrong time

	int currentStreak;
	int maxStreak;
	int totalNotes;
	int notesHit;
	int falseHits;

	int scoreChange;
	int meterChange;
	int totalScore;
	int topScore;	

	int multiplier;

	void updateTopScore();
	double getAverageMultiplier();

public:

	void update(const std::vector<Event_Data>&);
	Scoring();
	int getScoreChange();
	int getMeterChange();
	int getCurrentStreak();
	int getMultiplier();
	double getPercentage();
	int getRating();
};