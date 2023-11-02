#pragma once
#include <string>
class MyString
{
public:
	MyString();
	MyString(char c);
	MyString(const char* ch);
	MyString operator=(MyString a);
	~MyString();
	char operator[](int index);
	char operator+=(char c);
	char operator+=(const char* ch);
	char operator+=(MyString str);
	char at(int index);
	const char* c_str();
	size_t size();
	void clear();
	void push_back(char c);
	MyString replace(size_t pos , size_t count, MyString s);
	size_t find(const MyString& str, size_t pos = 0);
	size_t find(const char* ch, size_t pos = 0);
	size_t rfind(const MyString& str, int pos = -1);
	size_t rfind(const char* ch, int pos = -1);
	MyString substr(size_t pos = 0, int count = -1);
private:
	char* m_p;
	int m_len;
	int m_array_len;
	static const size_t npos = -1;
	std::string s;
};

