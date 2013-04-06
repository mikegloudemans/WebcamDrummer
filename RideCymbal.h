#pragma once
#include "GameObject.h"
#include "Vertex.h"
#include <vector>
#include <GL\freeglut.h>

class RideCymbal :
	public GameObject
{
private:
	std::vector<Vertex>						m_Vertices;
public:
	RideCymbal(const Vector& position);
	virtual void update(double elapsedTime);
	virtual void render();
	virtual bool collision(const Vector& otherObject);
	virtual void destroy();
};