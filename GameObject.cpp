#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const Vector& position) : m_Position(position.getX(), position.getY(), position.getZ()) { }