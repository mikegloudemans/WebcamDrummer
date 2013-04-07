#pragma once
#include "GameObject.h"
#include "FallingObject.h"
#include "CrashCymbal.h"
#include "SnareDrum.h"
#include "HighTom.h"
#include "LowTom.h"
#include "RideCymbal.h"
#include "Utility.h"
#include "Scoring.h"
#include "EventMonitor.h"
#include "Font.h"

#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>

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
	double										m_Fall_Rate;
	double										m_Pad_Time;

	int											m_Score;
	int											m_Meter;

	Scoring										m_Scoring;

	EventMonitor								m_EventMonitor;

	ObjectState									m_ObjectState;

	Font										m_Score_Font;

	std::vector<GameObject*>					m_Falling_Objects;
	std::vector<GameObject*>					m_Drums;

	CrashCymbal*								m_CrashCymbal;
	SnareDrum*									m_SnareDrum;
	HighTom*									m_HighTom;
	LowTom*										m_LowTom;
	RideCymbal*									m_RideCymbal;

	//private methods
	void parse_input_file(const std::string& fileName);

public:
PlayField(double screenWidth, double screenHeight, double fallRate, double padTime, const std::string& fileName);
	void update(double elapsedTime, const Vector& leftHand, const Vector& rightHand);
	void render();
};