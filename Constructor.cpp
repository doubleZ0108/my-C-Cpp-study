#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Array
{
private:
	int *m_p = NULL;
	int m_len = 0;
public:
	Array(int len);
	Array(const Array &buf);	//参数必须是const, 而且是引用类型
		//如果不是const则,如果arr1是const类型定义的,
		//nonconst的arr2在拷贝构造的时候就会报错没有合适的拷贝构造函数
		//
		//如果这里不是引用类型, 则在调用这个函数的时候
		//实参到形参的过程中就要调用这个拷贝构造函数,然后又要调,又要调,陷入死循环
		//C++语法上就不允许这样的事情发生

	~Array();

	int operator[](int index)const { return m_p[index]; }
	int &operator[](int index) { return m_p[index]; }

	Array &operator=(const Array &buf);	//注意参数类型和返回值类型
		//如果没有深拷贝赋值运算符, 则m_p会被arr1和arr3各释放一次,造成内存错误
		//返回值为&的目的不仅能够避免在返回数据的时候调用拷贝构造函数
		//还可以达到连续复制的目的 arr1=arr2=arr3=arr4;
		//注:除了有这个参数外还可以有其他参数,但是其他参数必须给出默认值

	int length()const { return m_len; }
	void display()const;
};

class Point
{
	friend ostream &operator<<(ostream &os, const Point &buf);
private:
	double _x = 0.0;
	double _y = 0.0;
public:
	Point() = default;

	//下两个是转换构造函数 Conversion Constructor
	//常规的作用四创建对象的时候调用已初始化
	//额外的作用是,定义完对象之后, 如果给对象赋值的变量不是对象的话就会来调用这里的转换构造函数
	//起到的其实是类型转换的作用, 把double类型转换为Point类型
	Point(double x) { _x = x; }
	Point(double x, double y) { _x = x; _y = y; }

	//类型转换函数 Type conversion function
	//把当前类类型转换为其他类型, 只能以成员函数的形式出现
	//因为要转换的目标类型已经明确的给出了,所以不需要再写返回值(不是没有,而是隐式的指明了返回类型)
	//参数也没有 (实际上参数也是默认的 this指针)
	operator double()const { return _x; }
};

int main(void)
{
	Array arr1(10);
	for (int i = 0; i < arr1.length(); ++i)
	{
		arr1[i] = i;
	}

	/*Test 1: 深拷贝构造函数和浅拷贝构造函数*/
	cout << endl << "*****Test 1: 深拷贝构造函数和浅拷贝构造函数*****" << endl;
	Array arr2(arr1);	//这里写 Array arr2 = arr1; 和这么写是一模一样的,都会调用拷贝构造函数

	arr2[3] = 99;	//这里因为自定义了深拷贝,所以修改arr2的数据,arr1不发生变化
					//但是如果没有自己显示定义,系统默认的浅拷贝函数,则arr1和arr2同时变化

	cout << "After changes of arr2: " << endl;
	cout << "arr1: "; arr1.display();
	cout << "arr2: "; arr2.display();

	/*Test 2: 重载赋值运算符*/
	cout << endl << "*****Test 2: 重载赋值运算符*****" << endl;
	Array arr3(4);
	for (int i = 11; i < 11 + arr3.length(); ++i)
	{
		arr3[i-11] = i;
	}
	
	cout << "At the beginning: " << endl;
	cout << "arr1: "; arr1.display();
	cout << "arr3: "; arr3.display();

	arr3 = arr1;

	arr3[3] = 234;	//没有重载的深拷贝赋值运算符, 则arr1的值也会被修改
	cout << "After arr3=arr1 && change of arr3: " << endl;
	cout << "arr1: "; arr1.display();
	cout << "arr3: "; arr3.display();


	/*Test 3: 转换构造函数*/
	cout << endl << "*****Test 3: 转换构造函数*****" << endl;
	Point point;
	point = 15.4;			//调用自定义的转换构造函数Point(double)
	cout << "After point = 15,4"; cout << point << endl;

	//先执行系统默认的转换模式,然后调用自定义的转换构造函数
	point = 'A';			//char --> int --> double --> Point
	cout << "After point = 'A'"; cout << point << endl;

	point = true;			//bool --> int --> double --> Point
	cout << "After point = true"; cout << point << endl;


	/*Test 4: 类型转换函数*/
	cout << endl << "*****Test 4: 类型转换函数*****" << endl;
	Point pt(24.6, 100);
	double ptx = pt;
	cout << "After type conversion function: ";
	cout << "ptx is " << ptx << endl;

	int bufx = Point(55.5, 66.6);	//先创建了匿名对象,在将Point转换为double, 再将double转换为int
	cout << "bufx is " << bufx << endl;

	system("pause");
	return 0;
}

Array::Array(int len)
	:m_len(len)
{
	m_p = new int[m_len];
}

Array::Array(const Array & buf)
//自己定义的拷贝构造函数为深拷贝
//而如果自己不显示定义,系统会自动定义一份,他定义的为浅拷贝
{
	this->m_len = buf.m_len;
	this->m_p = new int[m_len];
	memcpy(this->m_p, buf.m_p, this->m_len*sizeof(int));
}

Array::~Array()
{
	if (m_p)
	{
		delete[]m_p;
	}
}

Array & Array::operator=(const Array & buf)
{
	if (this != &buf)	//判断是否是给自己赋值
	{
		this->m_len = buf.m_len;

		if (this->m_p)
		{
			delete[]this->m_p;		//把原来的内存释放掉
		}

		this->m_p = new int[this->m_len];
		memcpy(this->m_p, buf.m_p, this->m_len * sizeof(int));
	}
	return *this;
}

void Array::display() const
{
	for (int i = 0; i < this->m_len; ++i)
	{
		cout << m_p[i] << ' ';
	}
	cout << endl;
}

ostream & operator<<(ostream & os, const Point & buf)
{
	cout << "(" << buf._x << ", " << buf._y << ")";
	return os;
}
