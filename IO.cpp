/*
		C++输入输出专题
	在C++的输入输出中, 编译系统对数据类型进行严格的检查, 凡是类型不正确的数据都不可能通过编译
	C++的I/O操作是 type safe的, 也是可扩展的

	(1)cin,cout并不是C++提供的语句,他们是iostream类的对象
	(2)iostream-通用输入输出流	fstream-输入输出文件流	strstream输入输出字符串流类

*/

#include <iostream>
#include <cstdlib>
#include <iomanip>	//输出控制符的头文件

using namespace std;
int main(void)
{
	/*cin cout*/
	//(1)不能使用cin把空格字符和回车换行符作为字符输入给字符变量, 它们将被跳过
	//	 如果想把他们两个输入个字符变量, 可以使用getchar函数
	cout << endl << "double test" << endl;
	double a = 123.456789012345;
	//以9位有效数字输出
	cout << setprecision(9) << a << endl;	

	//以9位小数输出
	cout << setiosflags(ios::fixed) << setprecision(9) << a << endl;
	cout << resetiosflags(ios::fixed);	//使用后会记忆的, 所以使用过setiosflags要reset

	//科学计数法输出
	cout << setiosflags(ios::scientific) << a << endl;


	cout << endl << "int test" << endl;
	int b = 1234;
	//十六进制输出
	cout << hex << b << endl;
	//八进制
	cout << oct << b << endl;
	//十进制
	cout << dec << b << endl;

	//设定字段宽度
	cout << setw(10) << b << endl;
	
	//设置填充字符
	cout << setfill('*') << setw(10) << b << endl;

	//输出正数时给出+号
	cout << setiosflags(ios::showpos) << b << endl;
	cout << resetiosflags(ios::showpos);

	//输出数据左对齐
	cout << setiosflags(ios::left) << setw(10) << b << endl;
	cout << resetiosflags(ios::left);




	/*cerr流对象*/
	//cerr流已被指定为与显示器关联, 也就意味着cerr流中的信息只能在显示器输出
	//在调试程序时, 往往不希望程序运行时的出错信息被送到其他文件, 而要求在显示器上及时输出
	//这是应使用cerr
	//并且cerr是不经过缓冲区的, 直接向显示器上输出有关信息

	system("pause");
	return 0;
}