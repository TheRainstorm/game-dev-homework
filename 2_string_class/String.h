#pragma once
#include <cstddef>

class String
{
private:
	char* m_pszStr;
	int m_iSize;
public:
	String(const char* str=nullptr);
	String(const String& str);
	~String();
	const char* get() const;			//获得字符串地址 第一个const 防止m_pszStr在类外被修改
	void set(const char* str);			//设置为新的字符串

	//util
	int length() const;
	int search(char ch);
	int search(const char* pattern);

	// 操作符重载
	const String& operator=(const String& str); //返回const：连续复制时，固定为右值而不可能成为左值；返回引用：在函数内不必进行拷贝。
	const String operator+(const String& str);	//返回非引用：返回值应是一个不同于两个操作数的新的对象。
	bool operator==(const String& str);
	bool operator>(const String& str);
	bool operator>=(const String& str);
	char operator[](int index);
};

