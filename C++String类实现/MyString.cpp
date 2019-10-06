#include "MyString.h"

MyString::MyString(const char* str)
{
	if (NULL == str) {
		m_data = new char[1];
		*m_data = '\0';
	}
	else {
		m_data = new char[strlen(str) + 1];
		strcpy(m_data,str);
	}
}

MyString::MyString(const MyString& rhs)
{
	if (rhs.m_data) {
		if (this != &rhs) {
			m_data = new char[strlen(rhs.m_data) + 1];
			strcpy(m_data, rhs.m_data);
		}
	}
	else {
		m_data = new char[1];
		*m_data = '\0';
	}
}

MyString& MyString::operator=(const MyString& rhs)
{
	if (this != &rhs){
		m_data = new char[strlen(rhs.m_data) + 1];
		strcpy(m_data,rhs.m_data);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& str)noexcept
{
	if (this != &str) {
		delete[] m_data;
		m_data = nullptr;
		m_data = str.m_data;
	}
	str.m_data = nullptr;
	return *this;
}

MyString::~MyString()
{
	if (m_data) {
		delete[] m_data;
		m_data = NULL;
	}
}

MyString MyString::operator+(const MyString& str)
{
	MyString cur;
	if (nullptr == str.m_data)
		cur = *this;
	else if (nullptr == this->m_data)
		cur = str;
	else {
		cur.m_data = new char[strlen(m_data) + strlen(str.m_data) + 1];
		strcpy(cur.m_data,m_data);
		strcat(cur.m_data,str.m_data);
	}
	return cur;
}

char& MyString::operator[](size_t index)
{
	if (index >= strlen(m_data))
		throw std::out_of_range("index out of range");
	else
		return m_data[index];
}

const char* MyString::c_str()
{
	return m_data;
}

bool MyString::operator==(const MyString& str)
{
	if (this != &str) {
		return strcmp(m_data,str.m_data) == 0;
	}
	return true;
}

MyString::MyString(MyString&& str) noexcept
{
	delete[] m_data;
	m_data = nullptr;
	m_data = str.m_data;
	str.m_data = nullptr;
}

std::ostream& operator << (std::ostream& os, const MyString& str) {
	if (str.m_data) {
		os << str.m_data << std::endl;
	}
	else
		os << ' ' << std::endl;
	return os;
}
std::istream& operator >> (std::istream& is, MyString& str) {
	is >> str.m_data;
	return is;
}
