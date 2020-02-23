// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

extern int global_outer_num;
//int global_outer_num = 10; //Error	LNK2005	"int global_outer_num" (?global_outer_num@@3HA) already defined in 
extern int static_global_outer_num;
void print_num_in_other();

int global_num = 0;
static int static_global_num = 1;

void print_num(int cnt) {
	int auto_num = 2;
	static int static_auto_num = 3;

	cout << "In print_num, cnt: " << cnt << endl;
	cout << "auto_num: " << auto_num << endl;
	cout << "static_auto_num: " << static_auto_num << endl;

	auto_num++;
	static_auto_num++;

	cout << "global_num: " << global_num << endl;
	cout << "static_global_num: " << static_global_num << endl;
	global_num++;
	static_global_num++;
}

int main()
{
	{
		int block_auto_num = 10;
	}
	/*
	The difference in ������
	*/
	//ȫ�ֱ����������κεط�(ͬһ�ļ�)���ã��ֲ�����ֻ���ڶ���ĺ�����(�����)����
	cout << "global_num: " << global_num << endl;
	cout << "static_global_num: " << static_global_num << endl;
	// cout <<"auto_num"<<auto_num<<endl; //error
	// cout <<"static_auto_num"<<static_auto_num<<endl; //error
	// cout <<"block_auto_num"<< block_auto_num <<endl; //error

	//�Ǿ�̬��ȫ�ֱ���������ͨ��extern���ļ����ã�����̬�Ĳ���
	cout << "global_outer_num: " << global_outer_num << endl;
	// cout <<"static_outer_global_num: "<<static_outer_global_num<<endl; //error
	//�Ǿ�̬��ȫ�ֱ���ͨ�����ļ����ڵĺ����ǿ������õ�
	print_num_in_other();

	/*
	The difference in ��������
	*/
	//�Ǿ�̬�ֲ�������ÿ�ε��ú���ʱ��������ջ�����·��䣬�������ý���ʱ���١�
	//��̬�ֲ������ڵ�һ�ζ���ʱ���洢�ڶ��У��������ý���ʱ�������٣���˿��Ա���ֵ��
	print_num(0);
	print_num(1);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
