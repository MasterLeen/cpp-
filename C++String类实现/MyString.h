#ifndef MYSTRING_H
#define MYSTRING_H
#include <string.h>//c语言的string库
#include <iostream>
class MyString {
public:
	MyString(const char* str = NULL);
	MyString(const MyString& rhs);
	MyString& operator = (const MyString& rhs);
	MyString& operator = (MyString&& str) noexcept;
	MyString(MyString&& str)noexcept;//移动构造函数
	~MyString();
	MyString operator + (const MyString& str);
	char& operator [] (size_t index);
	const char* c_str();
	bool operator == (const MyString& str);
	friend std::ostream& operator << (std::ostream& os,const MyString& str);
	friend std::istream& operator >> (std::istream& is,MyString& str);
	
private:
	char* m_data;
};
#endif
