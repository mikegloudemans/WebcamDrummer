#pragma once
#include "Vector.h"

class GameObject
{
protected:
	Vector				m_Position;
	bool				m_Destroyed;
public:
	GameObject(const Vector& position, bool destroyed = false);
	bool is_destroyed() { return m_Destroyed; }
	void reset() { m_Destroyed = false; }
	Vector get_position() { return Vector(m_Position.getX(), m_Position.getY(), m_Position.getZ()); }
	virtual void update(double elapsedTime) = 0;
	virtual void render() = 0;
	virtual bool collision(const Vector& otherObject) = 0;
	virtual void destroy() = 0;

};