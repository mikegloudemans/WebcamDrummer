#include "stdafx.h"
#include "Playfield.h"

PlayField::PlayField(double screenWidth, double screenHeight, const std::string& fileName)
{
	parse_input_file(fileName);

	double xIncrement = screenWidth / 5;

	m_Row1_X = -xIncrement * 2;
	m_Row2_X = -xIncrement;
	m_Row3_X = 0;
	m_Row4_X = xIncrement;
	m_Row5_X = xIncrement * 2;

	m_Drum_Y = -(screenHeight / 5) * 2;

	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row1_X, 0, -.1), .001));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row2_X, 0, -.1), .001));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row3_X, 0, -.1), .001));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row4_X, 0, -.1), .001));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row5_X, 0, -.1), .001));


	m_CrashCymbal = new CrashCymbal(Vector(m_Row1_X, m_Drum_Y, -.1));
	m_SnareDrum = new SnareDrum(Vector(m_Row2_X, m_Drum_Y, -.1));;
	m_HighTom = new HighTom(Vector(m_Row3_X, m_Drum_Y, -.1));
	m_LowTom = new LowTom(Vector(m_Row4_X, m_Drum_Y, -.1));
	m_RideCymbal = new RideCymbal(Vector(m_Row5_X, m_Drum_Y, -.1));
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

	m_CrashCymbal->render();
	m_SnareDrum->render();
	m_HighTom->render();
	m_LowTom->render();
	m_RideCymbal->render();
}