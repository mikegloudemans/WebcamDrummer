#pragma once

#include "Event_Data.h"
#include "ObjectState.h"

class EventMonitor
{
private:

	const static int numDrums = 5;
	std::vector<Event_Data> events;	
	std::vector<bool> drumsOccupied;
	std::vector<bool> drumsHit;
	void detectDrumHits(ObjectState&);

public:
	std::vector<Event_Data> update(ObjectState&);
	EventMonitor();
};