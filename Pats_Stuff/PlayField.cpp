#include "stdafx.h"
#include "Playfield.h"

PlayField::PlayField(double screenWidth, double screenHeight, double fallRate, const std::string& fileName)
{
	parse_input_file(fileName);

	double xIncrement = screenWidth / 5;

	m_Row1_X = -xIncrement * 2;
	m_Row2_X = -xIncrement;
	m_Row3_X = 0;
	m_Row4_X = xIncrement;
	m_Row5_X = xIncrement * 2;

	m_Drum_Y = -(screenHeight / 5) * 2;

	m_Fall_Rate = 

	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row1_X, 0, -.1), fallRate));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row2_X, 0, -.1), fallRate));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row3_X, 0, -.1), fallRate));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row4_X, 0, -.1), fallRate));
	m_Falling_Objects.push_back(new FallingObject(Vector(m_Row5_X, 0, -.1), fallRate));


	m_CrashCymbal = new CrashCymbal(Vector(m_Row1_X, m_Drum_Y, -.1));
	m_SnareDrum = new SnareDrum(Vector(m_Row2_X, m_Drum_Y, -.1));;
	m_HighTom = new HighTom(Vector(m_Row3_X, m_Drum_Y, -.1));
	m_LowTom = new LowTom(Vector(m_Row4_X, m_Drum_Y, -.1));
	m_RideCymbal = new RideCymbal(Vector(m_Row5_X, m_Drum_Y, -.1));
}

void PlayField::parse_input_file(const std::string& fileName)
{
	std::ifstream level("poop.txt");
	std::string line;
	std::vector<std::string> splitLine;

	if(level.is_open())
	{
		while(level.good())
		{
			std::getline(level, line);

			if(line.size() == 0)
			{
				continue;
			}

			split(line, ',', splitLine);
			splitLine.at(0) = splitLine.at(0).substr(2, splitLine.at(0).npos);

			if(!splitLine.at(0).compare(""))
			{
				line.clear();
				splitLine.clear();
				continue;
			}

			for(std::vector<std::string>::iterator iter = splitLine.begin(); iter != splitLine.end(); ++iter)
			{
				double test = atof((*iter).c_str());
				char poop = 'a';
			}

			line.clear();
			splitLine.clear();
		}
	}
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