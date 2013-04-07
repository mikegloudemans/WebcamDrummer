#pragma once

class QuadraticTween
{
private:
	double					m_Time;
	double					m_Speed;
	double					m_Current_Value;
public:
	QuadraticTween(double time, double speed) : m_Time(time), m_Speed(speed) { }
	double get_value()
};