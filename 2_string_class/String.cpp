#include "String.h"
#include <cstring>
#include <iostream>

String::String(const char* str) {
	m_pszStr = nullptr;
	this->set(str);
}

String::String(const String& str) {
	m_pszStr = nullptr;
	this->set(str.get());
}

const char* String::get() const {
	return m_pszStr;
}

void String::set(const char* str) {
	delete[]m_pszStr; 
	if (str == nullptr) {
		m_pszStr = nullptr;
		m_iSize = 0;
	}
	else {
		m_iSize = strlen(str);
		m_pszStr = new char[m_iSize + 1];
		#pragma warning(suppress : 4996)
		strcpy(m_pszStr, str);
	}
}

String::~String() {
	delete[]m_pszStr;
}

int String::length() const {
	return m_iSize;
}

int String::search(char ch) {
	char* ptr = this->m_pszStr;
	while (*ptr) {
		if (*ptr == ch) {
			return ptr-this->m_pszStr;
		}
		ptr++;
	}
	return -1;
}

int String::search(const char *pattern) {
	char* ptr = this->m_pszStr;
	int patternLength = strlen(pattern);

	int i, j;
	for (i = 0; i < (this->length() - patternLength); i++) {
		for (j = 0; j < patternLength; j++) {
			if (ptr[i + j] != pattern[j]) {
				break;
			}
		}
		if (j == patternLength) {
			return i;
		}
	}
	return -1;
}

//ÔËËã·ûÖØÔØ
const String& String::operator=(const String &str) {
	this->set(str.get());
	return *(this);
}

const String String::operator+(const String& str) {
	String sum;
	sum.m_iSize = this->length() + str.length() + 1;
	sum.m_pszStr = new char[sum.m_iSize];
	#pragma warning(suppress : 4996)
	strcpy(sum.m_pszStr, this->get());
	#pragma warning(suppress : 4996)
	strcat(sum.m_pszStr, str.get());
	return sum;
}

bool String::operator==(const String& str) {
	return strcmp(this->get(), str.get()) == 0 ? true : false;
}

bool String::operator>(const String& str) {
	return strcmp(this->get(), str.get()) > 0 ? true : false;
}

bool String::operator>=(const String& str) {
	return strcmp(this->get(), str.get()) >= 0 ? true : false;
}

char String::operator[](int index) {
	if (index < 0 || index >= this->length()) {
		std::cout << "index overflow" << std::endl;
		exit(1);
	}
	char* ptr = this->m_pszStr;
	while (index--) {
		ptr++;
	}
	return *ptr;
}