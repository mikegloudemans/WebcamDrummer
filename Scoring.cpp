#include "Scoring.h"

void Scoring::update(std::vector<Event_Data> events)
{
	for(int i=0; i < events.size(); i++){
		Event_Data data = events[i];
		if (data.success == true)
		{
			// Successfully hit note.
			currentStreak++;
			if (currentStreak > maxStreak)
			{
				maxStreak = currentStreak;
			}
			totalNotes++;
			notesHit++;
		}
		if (data.success == false && data.note_missed == true)
		{
			// Missed note that was supposed to be hit.
			currentStreak++;

		}
		if (data.success == false && data.note_missed == false)
		{
			// Hit when there wasn't a note to be hit
			current
		}
	}
}

int Scoring::getScoreChange()
{
}

int Scoring::getMeterChange()
{
}