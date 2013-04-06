#include "stdafx.h"
#include "Playfield.h"

PlayField::PlayField(double screenWidth, const std::string& fileName)
{
	parse_input_file(fileName);

	double xIncrement = screenWidth / 5;

	m_Row1_X = -2.0f * xIncrement;
	m_Row2_X = -xIncrement;
	m_Row3_X = 0;
	m_Row4_X = xIncrement;
	m_Row5_X = 2.0f * xIncrement;

	/*m_Row1_X = -.4;
	m_Row2_X = -.2;
	m_Row3_X = 0;
	m_Row4_X = .2;
	m_Row5_X = .4;*/

	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row1_X, 0, -.1), .1));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row2_X, 0, -.1), .1));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row3_X, 0, -.1), .1));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row4_X, 0, -.1), .1));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row5_X, 0, -.1), .1));
}

void PlayField::parse_input_file(const std::string& fileName)
{

}

void PlayField::update(double elapsedTime)
{
	for(unsigned int i = 0; i < m_Falling_Objects.size(); ++i)
	{
		m_Falling_Objects[i]->update(elapsedTime);
	}
}

void PlayField::render()
{
	for(unsigned int i = 0; i < m_Falling_Objects.size(); ++i)
	{
		m_Falling_Objects[i]->render();
	}
}