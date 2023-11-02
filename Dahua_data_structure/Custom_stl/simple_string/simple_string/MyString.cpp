#include "stdafx.h"
#include "MyString.h"
#include <string.h>


MyString::MyString()
{
	m_array_len = 0x10;
	m_p = new char[m_array_len];
	m_len = 0;
}


MyString::MyString(char c)
{
	m_array_len = 0x10;
	m_p = new char[m_array_len];
	m_p[0] = c;
	m_len = 1;
}

MyString::MyString(const char* ch)
{
	size_t len = strlen(ch);
	if (len>8)
	{
		m_array_len = 2 * len;
		m_p = new char[m_array_len];
	}
	else
	{
		m_array_len = 0x10;
		m_p = new char[m_array_len];
	}
	memcpy(m_p, ch, len);
	m_len = len;
}

MyString::~MyString()
{
}
