#include "stdafx.h"
#include "SnareDrum.h"

SnareDrum::SnareDrum(const Vector& position)  : GameObject(position)
{
	//generate vertices

	Vertex topLeft;
	memset(&topLeft, 0, sizeof(Vertex));
	topLeft.x = -.2;
	topLeft.y = .2;
	m_Vertices.push_back(topLeft);

	Vertex topRight;
	memset(&topRight, 0, sizeof(Vertex));
	topRight.x = .2;
	topRight.y = .2;
	m_Vertices.push_back(topRight);

	Vertex bottomRight;
	memset(&bottomRight, 0, sizeof(Vertex));
	bottomRight.x = .2;
	bottomRight.y = -.2;
	m_Vertices.push_back(bottomRight);

	Vertex bottomLeft;
	memset(&bottomLeft, 0, sizeof(Vertex));
	bottomLeft.x = -.2;
	bottomLeft.y = -.2;
	m_Vertices.push_back(bottomLeft);
}

void SnareDrum::update(double elapsedTime)
{
	
}

void SnareDrum::render()
{
	glPushMatrix();
	glPushClientAttrib(GL_VERTEX_ARRAY);
	glPushAttrib(GL_CURRENT_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, sizeof(Vertex), &m_Vertices[0]);
	glTranslated(m_Position.getX(), m_Position.getY(), m_Position.getZ());
	glScaled(.02, .02, .02);
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_QUADS, 0, m_Vertices.size());
	glPopAttrib();
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopClientAttrib();
	glPopMatrix();
}

bool SnareDrum::collision(const Vector& otherObject)
{
	return false;
}

void SnareDrum::destroy()
{

}