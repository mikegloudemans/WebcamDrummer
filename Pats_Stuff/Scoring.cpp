#include "stdafx.h"
#include "Scoring.h"
#include <algorithm>

Scoring::Scoring()
{
	currentStreak = 0;
	maxStreak = 0;
	totalNotes = 0;
	goodHits = 0;
	awesomeHits = 0;
	falseHits = 0;
	scoreChange = 0;
	meterChange = 0;
	totalScore = 0;
	topScore = 0;
	multiplier = 1;
}

void Scoring::update(const std::vector<Event_Data>& events)
{
	scoreChange = 0;
	meterChange = 0;

	// Not sure if this is really the right way to do this
	for(int i=0; i < events.size(); i++){

		Event_Data data = events[i];

		if (data.success == true)
		{
			// Successfully hit note.
			currentStreak++;
			maxStreak = std::max(currentStreak, maxStreak);
			totalNotes++;
			//notesHit++;
			meterChange++;
			scoreChange += pointsPerNote * multiplier;

			// Penalty for having slightly bad timing in hitting the note.
			// Might get rid of this if it makes the game too difficult.
			if (data.distance_from_center > tolerance)
			{
				scoreChange -= data.distance_from_center - tolerance;
				goodHits++;
			}
			else
			{
				awesomeHits++;
			}

			// Update mulitiplier based on current streak.
			// Let 5 be the maximum attainable multiplier.
			multiplier = std::min(1 + currentStreak / 10, 5);
			updateTopScore();
		}

		if (data.success == false && data.note_missed == true)
		{
			// Missed note that was supposed to be hit.
			currentStreak = 0;
			totalNotes++;
			meterChange--;
			multiplier = 1;
			updateTopScore();
		}

		if (data.success == false && data.note_missed == false)
		{
			// Hit when there wasn't a note to be hit
			currentStreak = 0;
			falseHits++;
			meterChange--;
			scoreChange -= badHitPenalty;
			multiplier = 1;
		}
	}

	totalScore += scoreChange;
}

void Scoring::updateTopScore()
{
	// Keep track of the maximum attainable score.
	int topMultiplier = totalNotes / 10;
	topScore += topMultiplier * pointsPerNote;
}

int Scoring::getScoreChange()
{
	return scoreChange;
}

int Scoring::getMeterChange()
{
	return meterChange;
}

int Scoring::getCurrentStreak()
{
	return currentStreak;
}

int Scoring::getMultiplier()
{
	return multiplier;
}

double Scoring::getPercentage()
{
	// Percentage of notes hit
	return (double)(goodHits + awesomeHits)/ totalNotes;
}

double Scoring::getAverageMultiplier()
{
	return (double) totalScore / (pointsPerNote * totalNotes);
}

int Scoring::getRating()
{
	// Return the user's rating on a scale of 1 to 5.
	return (int) (getAverageMultiplier() + 0.5);
}

ScoreStats Scoring::getStats()
{
	ScoreStats ss;
	ss.awesomeHits = awesomeHits;
	ss.falseHits = falseHits;
	ss.goodHits = goodHits;
	ss.maxStreak = maxStreak;
	ss.missedHits = (totalNotes - goodHits - awesomeHits);
	ss.percentage = getPercentage();
	ss.rating = getRating();
	ss.totalScore = totalScore;

	return ss;
}