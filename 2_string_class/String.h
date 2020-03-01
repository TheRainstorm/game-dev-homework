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
	const char* get() const;			//����ַ�����ַ ��һ��const ��ֹm_pszStr�����ⱻ�޸�
	void set(const char* str);			//����Ϊ�µ��ַ���

	//util
	int length() const;
	int search(char ch);
	int search(const char* pattern);

	// ����������
	const String& operator=(const String& str); //����const����������ʱ���̶�Ϊ��ֵ�������ܳ�Ϊ��ֵ���������ã��ں����ڲ��ؽ��п�����
	const String operator+(const String& str);	//���ط����ã�����ֵӦ��һ����ͬ���������������µĶ���
	bool operator==(const String& str);
	bool operator>(const String& str);
	bool operator>=(const String& str);
	char operator[](int index);
};

