#include "stdafx.h"
#include "Playfield.h"

PlayField::PlayField(double screenWidth, double screenHeight, double fallRate, double padTime, const std::string& fileName) : m_Scoring(Scoring()), m_EventMonitor(EventMonitor()),
	m_Score_Font("Score: ", std::wstring(L"Arial Black"), Vector(0, 0, -.1), Vector(0.0, 0.0, 1.0), 36)
{
	m_Score = 0;

	m_Meter = 0;

	double xIncrement = screenWidth / 5;

	m_Row1_X = -xIncrement * 2;
	m_Row2_X = -xIncrement;
	m_Row3_X = 0;
	m_Row4_X = xIncrement;
	m_Row5_X = xIncrement * 2;

	m_Drum_Y = -(screenHeight / 5) * 2;

	m_Fall_Rate = fallRate;

	m_Pad_Time = padTime;

	parse_input_file(fileName);

	m_CrashCymbal = new CrashCymbal(Vector(m_Row1_X, m_Drum_Y, -.1));
	m_SnareDrum = new SnareDrum(Vector(m_Row2_X, m_Drum_Y, -.1));;
	m_HighTom = new HighTom(Vector(m_Row3_X, m_Drum_Y, -.1));
	m_LowTom = new LowTom(Vector(m_Row4_X, m_Drum_Y, -.1));
	m_RideCymbal = new RideCymbal(Vector(m_Row5_X, m_Drum_Y, -.1));

	m_Drums.push_back(m_CrashCymbal);
	m_Drums.push_back(m_SnareDrum);
	m_Drums.push_back(m_HighTom);
	m_Drums.push_back(m_LowTom);
	m_Drums.push_back(m_RideCymbal);

	m_ObjectState.yThreshold = -1;
	m_ObjectState.drums = &m_Drums;
	m_ObjectState.vec = &m_Falling_Objects;
}

void PlayField::update_score()
{
	////loop to see if any of the drums are being touched

	//for(unsigned int i = 0; i < m_Falling_Objects.size(); ++i)
	//{
	//	for(unsigned int j = 0; j < m_Drums.size(); ++j)
	//	{
	//		if(m_Drums[j]->collision(m_Falling_Objects[i]->get_position()))
	//		{
	//			if(m_Drums[j]->collision(m_ObjectState.leftHand) || m_Drums[j]->collision(m_ObjectState.rightHand)) 
	//			{
	//				m_Score += 10;
	//			}
	//		}
	//	}
	//}
}

void PlayField::parse_input_file(const std::string& fileName)
{
	std::ifstream level(fileName);
	std::string line;
	std::vector<std::string> splitLine;
	int playspaceColumn = 1;

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
				(playspaceColumn == 5) ? playspaceColumn = 1 : ++playspaceColumn;
				continue;
			}

			for(std::vector<std::string>::iterator iter = splitLine.begin(); iter != splitLine.end(); ++iter)
			{
				double time = atof((*iter).c_str());
				double y = m_Drum_Y + m_Pad_Time + m_Fall_Rate * time;

				switch(playspaceColumn)
				{
				case 1:
					m_Falling_Objects.push_back(new FallingObject(Vector(m_Row1_X, y, -.1), m_Fall_Rate));
					break;
				case 2:
					m_Falling_Objects.push_back(new FallingObject(Vector(m_Row2_X, y, -.1), m_Fall_Rate));
					break;
				case 3:
					m_Falling_Objects.push_back(new FallingObject(Vector(m_Row3_X, y, -.1), m_Fall_Rate));
					break;
				case 4:
					m_Falling_Objects.push_back(new FallingObject(Vector(m_Row4_X, y, -.1), m_Fall_Rate));
					break;
				case 5:
					m_Falling_Objects.push_back(new FallingObject(Vector(m_Row5_X, y, -.1), m_Fall_Rate));
					break;
				}
			}

			line.clear();
			splitLine.clear();
			(playspaceColumn == 5) ? playspaceColumn = 1 : ++playspaceColumn;
		}
	}
}

DWORD WINAPI play_song(LPVOID args)
{
	return PlaySound(TEXT("U Cant Touch This.wav"), NULL, SND_SYNC);
}

void PlayField::update(double elapsedTime, const Vector& leftHand, const Vector& rightHand)
{
	DWORD threadID;
	int value = 10;
	CreateThread(NULL, 0, play_song, &value, 0, &threadID);

	for(unsigned int i = 0; i < m_Falling_Objects.size(); ++i)
	{
		m_Falling_Objects[i]->update(elapsedTime);
	}

	m_ObjectState.leftHand = leftHand;
	m_ObjectState.rightHand = rightHand;

	update_score();

	m_Scoring.update(m_EventMonitor.update(m_ObjectState));

	m_Score += m_Scoring.getScoreChange();

	std::string result;

	std::ostringstream str;

	str << m_Score;

	m_Score_Font.set_text(std::string("Score: ") + std::string(str.str()));
}

void PlayField::render()
{
	m_CrashCymbal->render();
	m_SnareDrum->render();
	m_HighTom->render();
	m_LowTom->render();
	m_RideCymbal->render();

	m_Score_Font.render();

	glDisable(GL_DEPTH_TEST);

	for(unsigned int i = 0; i < m_Falling_Objects.size(); ++i)
	{
		m_Falling_Objects[i]->render();
	}

	glEnable(GL_DEPTH_TEST);
}