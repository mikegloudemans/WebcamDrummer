#pragma once
#include "Vector.h"

class GameObject
{
protected:
	Vector				m_Position;
public:
	GameObject(const Vector& position);
	virtual void update(double elapsedTime) = 0;
	virtual void render() = 0;
	virtual bool collision(const Vector& otherObject) = 0;
	virtual void destroy() = 0;
};