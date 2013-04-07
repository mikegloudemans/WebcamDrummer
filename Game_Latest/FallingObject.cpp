#include "stdafx.h"
#include "FallingObject.h"

FallingObject::FallingObject(const Vector& position, double fallRate) : GameObject(position),
	m_Fall_Rate(fallRate) 
{ 
	//generate vertices

	Vertex topLeft;
	memset(&topLeft, 0, sizeof(Vertex));
	topLeft.x = -.002;
	topLeft.y = .002;
	m_Vertices.push_back(topLeft);

	Vertex topRight;
	memset(&topRight, 0, sizeof(Vertex));
	topRight.x = .002;
	topRight.y = .002;
	m_Vertices.push_back(topRight);

	Vertex bottomRight;
	memset(&bottomRight, 0, sizeof(Vertex));
	bottomRight.x = .002;
	bottomRight.y = -.002;
	m_Vertices.push_back(bottomRight);

	Vertex bottomLeft;
	memset(&bottomLeft, 0, sizeof(Vertex));
	bottomLeft.x = -.002;
	bottomLeft.y = -.002;
	m_Vertices.push_back(bottomLeft);
}

void FallingObject::update(double elapsedTime)
{
	//for(unsigned int i = 0; i < m_Vertices.size(); ++i)
	//{
		m_Position.setY(m_Position.getY() - m_Fall_Rate * elapsedTime);
    //}
}



void FallingObject::render()
{
	glPushMatrix();
	glPushClientAttrib(GL_VERTEX_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, sizeof(Vertex), &m_Vertices[0]);
	glTranslated(m_Position.getX(), m_Position.getY(), m_Position.getZ());
	//glScaled(.01, .01, .01);
	glDrawArrays(GL_QUADS, 0, m_Vertices.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopClientAttrib();
	glPopMatrix();
}

bool FallingObject::collision(const Vector& otherObject)
{
	return abs(m_Position.getY() - otherObject.getY()) < .1;
}

void FallingObject::destroy()
{
	m_Destroyed = true;
}