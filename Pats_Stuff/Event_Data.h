#pragma once

struct Event_Data
{
	bool success;
	bool note_missed;
	double distance_from_center;

	Event_Data(bool success, bool note_missed, double distance_from_center)
		:success(success), note_missed(note_missed), distance_from_center(distance_from_center) { }
};