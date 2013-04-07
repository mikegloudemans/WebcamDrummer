#include "stdafx.h"
#include "Font.h"

Font::Font(const std::string& string, const std::wstring& font, const Vector& position, const Vector& color, int height) : m_String(string), m_Position(position), m_Font(font), m_Color(color), m_Height(height)
{
	build_font();
}

void Font::build_font()
{
	HFONT font;
	HFONT oldfont;
	m_Base = glGenLists(96);

	font = CreateFont(	-m_Height,						// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						m_Font.c_str());			// Font Name

	//char title[300];
	//GetWindowTextA(GetForegroundWindow(), title, 300);

	m_HDC = GetDC(GetForegroundWindow());
	oldfont = (HFONT)SelectObject(m_HDC, font);
	wglUseFontBitmaps(m_HDC, 32, 96, m_Base);
	SelectObject(m_HDC, oldfont);
	DeleteObject(font);
}

void Font::set_text(const std::string& newString) 
{
	m_String = newString; 
}

void Font::render()
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glTranslated(0, 0, m_Position.getZ());
	glColor3d(m_Color.getX(), m_Color.getY(), m_Color.getZ());
	glRasterPos2d(m_Position.getX(), m_Position.getY());
	char text[256];
	
	for(unsigned int i = 0; i < m_String.size(); i++)
	{
		text[i] = m_String.at(i);
	}

	glListBase(m_Base - 32);
	glCallLists(m_String.size(), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
	glPopMatrix();
}

Font::~Font()
{
	glDeleteLists(m_Base, 96);
}
