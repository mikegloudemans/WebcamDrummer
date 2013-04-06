#pragma once

struct Event_Data
{
	bool success;
	bool note_missed;
	double distance_from_center;

	Event_Data(bool s, bool n, double d)
		:success(s), note_missed(n), distance_from_center(d) {}
};