#pragma once
#include <vector>
#include "Event_Data.h"
#include "ScoreStats.h"

class Scoring
{
private:

	static const int pointsPerNote = 100;
	static const int badHitPenalty = 25;		// Penalty for hitting at wrong time
	static const int tolerance = 25;			// Maximum allowable distance from center before points are deducted.

	int currentStreak;
	int maxStreak;
	int totalNotes;
	int goodHits;
	int awesomeHits;
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

	int getMultiplier();
	int getCurrentStreak();
	int getMaxStreak();
	double getPercentage();
	int getRating();

	ScoreStats getStats();

};