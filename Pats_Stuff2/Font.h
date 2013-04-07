#pragma once
#include "Vector.h"
#include <string>
#include <Windows.h>
#include <GL\freeglut.h>

class Font
{
private:
	std::string					m_String;
	std::wstring				m_Font;
	Vector						m_Position;
	Vector						m_Color;
	GLuint						m_Base;
	HDC							m_HDC;
	int							m_Height;
	void build_font();
public:
	Font(const std::string& string, const std::wstring& font, const Vector& position, const Vector& color, int height);
	void set_text(const std::string& newString);
	void set_position(const Vector& newPosition) { m_Position = newPosition; }
	void render();
	~Font();
};