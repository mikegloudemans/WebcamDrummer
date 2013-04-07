#include "stdafx.h"
#include "EventMonitor.h"

EventMonitor::EventMonitor()
{
	for (int i = 0; i < numDrums; i++)
	{
		// Initialize vectors
		drumsOccupied.push_back(false); // Default to true so first frame doesn't detect false hits.
		drumsHit.push_back(false);
	}
}

void EventMonitor::detectDrumHits(ObjectState& gameState)
{
	// Determine whether a drum has been hit in the current frame.
	for(std::vector<GameObject*>::iterator it = gameState.drums->begin(); it != gameState.drums->end(); ++it)
	{
		int index = it - gameState.drums->begin();

		if ((*it)->collision(gameState.leftHand) || (*it)->collision(gameState.rightHand))
		{
			if (!drumsOccupied[index])
			{
				drumsHit[index] = true;
				drumsOccupied[index] = true;
			}
			else
			{
				drumsHit[index] = false;
			}
		}
		else
		{
			drumsOccupied[index] = false;
		}
	}
}

std::vector<Event_Data> EventMonitor::update(ObjectState& gameState)
{
	// Generates a vector of all the scoring events that should be addressed in a given frame.

	events.clear();

	detectDrumHits(gameState);

	// Iterate through all "notes" in the game to see if they should trigger
	// any scoring events.
	for(std::vector<GameObject*>::iterator it = gameState.vec->begin(); it != gameState.vec->end(); ++it) 
	{
		if ((*it)->is_destroyed())
		{
			// Ignore notes that have already been destroyed.
			continue;
		}
		if ((*it)->get_position().getY() < gameState.yThreshold)
		{
			// Destroy notes that have gone off the board,
			// and notify scoring system that they have 
			// been missed.
			(*it)->destroy();
			Event_Data ed = Event_Data(false,true,0);
			events.push_back(ed);
			continue;
		}
		for (std::vector<GameObject*>::iterator it_drums = gameState.drums->begin(); it_drums != gameState.drums->end(); ++it_drums)
		{
			// Check for collisions between notes and drums.
			int drumIndex = it_drums - gameState.drums->begin();

			if ((*it)->collision((*it_drums)->get_position()))
			{
				if (drumsHit[drumIndex])
				{
					// Drum was hit at correct time.
					(*it)->destroy();
					Event_Data ed = Event_Data(true,false,0);
					events.push_back(ed);

					// Update drumsHit vector to confirm that drum was correctly hit.
					drumsHit[drumIndex] = false;
					
					break;
				}
			}
		}
	}

	for (int i = 0; i < numDrums; i++)
	{
		// For drums that were hit but didn't match, add false hit events.
		if (drumsHit[i])
		{
			Event_Data ed = Event_Data(false,false,0);
			events.push_back(ed);
		}
	}
	
	return events;
}