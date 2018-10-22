#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
using namespace std;

void func_inner()
{
	throw "Unknown Exception";
	cout << "[1]This statement will not be excuted" << endl;
}
void func_outer()
{
	func_inner();
	cout << "[2]This statement will not be excuted" << endl;
}
int main(void)
{
	string str = "hello world";
	try
	{
		char ch2 = str.at(100);	//at()������⵽�±�Խ����׳�һ���쳣
		cout << ch2 << endl;
	}
	catch (exception &e)
	{
		cout << ".at()out of bound" << endl;
	}

	try
	{
		//try���е�����ĳ������,�ú����е����������һ������,�������ĺ����׳����쳣
		func_outer();	
		cout << "[3]This statement will not be excuted" << endl;
		/*
		ֻҪ�׳����쳣,ִ�����ͻ����ź����ĵ�����������,ֱ������try��ֹͣ
		�ڻ��˵Ĺ�����, ��������ʣ�µĴ���(���к�����δ��ִ�еĴ���), ȫ���ᱻ����
		��Ҳû��ִ�еĻ�����
		*/

	}
	catch (const char* e)
	{
		cout << e << endl;
	}
	system("pause");
	return 0;
}