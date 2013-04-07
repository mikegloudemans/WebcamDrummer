#pragma once
#include "Vector.h"

class GameObject
{
private:
	bool				m_Destroyed;
protected:
	Vector				m_Position;
public:
	GameObject(const Vector& position, bool destroyed = false);
	bool is_destroyed() { return m_Destroyed; }
	void reset() { m_Destroyed = false; }
	virtual void update(double elapsedTime) = 0;
	virtual void render() = 0;
	virtual bool collision(const Vector& otherObject) = 0;
	virtual void destroy() = 0;

};