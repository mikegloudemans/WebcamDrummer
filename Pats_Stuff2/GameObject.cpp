#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const Vector& position, bool destroyed) : m_Position(position.getX(), position.getY(), position.getZ()), m_Destroyed(destroyed) { }