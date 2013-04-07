#pragma once
#include "GameObject.h"
#include "FallingObject.h"
#include "CrashCymbal.h"
#include "SnareDrum.h"
#include "HighTom.h"
#include "LowTom.h"
#include "RideCymbal.h"

#include <vector>
#include <string>

/*
Class to represent and monitor the playfield for the game. Keeps track of the falling objects
and passes events on to the scoring system when necessary.
*/

class PlayField
{
private:
	double										m_Row1_X;
	double										m_Row2_X;
	double										m_Row3_X;
	double										m_Row4_X;
	double										m_Row5_X;
	double										m_Drum_Y;

	std::vector<GameObject*>					m_Falling_Objects;

	CrashCymbal*								m_CrashCymbal;
	SnareDrum*									m_SnareDrum;
	HighTom*									m_HighTom;
	LowTom*										m_LowTom;
	RideCymbal*									m_RideCymbal;

	//private methods
	void parse_input_file(const std::string& fileName);

public:
	PlayField(double screenWidth, double screenHeight, const std::string& fileName);
	void update(double elapsedTime);
	void render();
};