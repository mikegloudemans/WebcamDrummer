#pragma once
#include <vector>
#include "GameObject.h"
#include "Vector.h"

// Struct containing all drum and note objects in the current game state

struct ObjectState
{
	int yThreshold;

	std::vector<GameObject*>& drums;
	std::vector<GameObject*>& vec;
	
	Vector& leftHand;
	Vector& rightHand;
};