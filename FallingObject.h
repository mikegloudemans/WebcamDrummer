#pragma once
#include "GameObject.h"
#include "Vector.h"
#include "Vertex.h"
#include <vector>
#include <GL\freeglut.h>

/*
Class to represent the falling objects seen in the game.
*/

class FallingObject :
	public GameObject
{
private:
	double						m_Fall_Rate;
	std::vector<Vertex>			m_Vertices;
public:
	FallingObject(const Vector& position, double fallRate);
	virtual void update(double elapsedTime);
	virtual void render();
	virtual bool collision(const Vector& otherObject);
	virtual void destroy();
};