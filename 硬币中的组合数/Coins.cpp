/*
*组合数学项目:	
*		"硬币中的组合数"
* 比较三种货币（人民币、美元、欧元）中硬币构成各自货币里10元的组合数。对比说明每种硬币的表现力
* 人民币有六种面额的硬币，分别是1分、2分、5分、1角、5角、1元。
* 美元有六种面额的硬币，分别是1美分、5美分、10美分、25美分，50美分、1美元。
* 欧元有八种面额的硬币，分别是 1欧分、2欧分、5欧分、10欧分、20欧分、50欧分、1欧元和2欧元。
*
*
* 参考资源:
*		https://www.cnblogs.com/python27/archive/2013/09/05/3303721.html
*/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void Combination(const vector<int> &coins, vector<vector<int> > &result, const int amount=1000)
{
	//把0种硬币组成任意金额的位置置为0
	for (int sum = 0; sum <= amount; ++sum)
	{ result[0][sum] = 0; }

	//任意硬币数量组成0元有1种可能
	for (int i = 0; i <= coins.size(); ++i)
	{
		result[i][0] = 1;
	}


	for (int i = 1; i <= coins.size(); ++i)
	{
		for (int sum = 1; sum <= amount; ++sum)
		{
			for (int k = 0; k <= sum / coins[i-1]; ++k)
			{
				result[i][sum] += result[i - 1][sum - k * coins[i-1]];	
					//conins的i-1位置标识着当前研究的硬币总种类的最后一种
			}
		}
	}
}
void showConbination(const vector<vector<int> >&Yuan, const vector<vector<int> >&Dollar
	, const vector < vector<int >> &Euro, const int amount = 1000)
{
	cout << setw(10) << "amount"
		<< setw(10) << "Yuan"
		<< setw(10) << "Dollar"
		<< setw(10) << "Euro" << endl;

	for (int sum = 1; sum <= amount; ++sum)
	{
		cout << setw(10) << sum;
		cout << setw(10) << Yuan[Yuan.size()-1][sum];
		cout << setw(10) << Dollar[Dollar.size()-1][sum];
		cout << setw(10) << Euro[Euro.size()-1][sum];
		cout << endl;
	}
}

int main(void)
{
	const int amount = 1000;

	vector<int> Yuan = { 1,2,5,10,50,100 };
	vector<vector<int> >ComYuan(Yuan.size()+1, vector<int>(amount+1, 0));	//增加0种硬币的情况 和 0元钱的情况
	Combination(Yuan, ComYuan);
	//cout << ComYuan[Yuan.size()][amount] << endl;
	
	vector<int> Dollar = { 1,5,10,25,50,100 };
	vector<vector<int> > ComDollar(Dollar.size() + 1, vector<int>(amount + 1, 0));
	Combination(Dollar, ComDollar);
	//cout << ComDollar[Dollar.size()][amount] << endl;

	vector<int> Euro = { 1,2,5,10,20,50,100,200 };
	vector<vector<int> > ComEuro(Euro.size() + 1, vector<int>(amount + 1, 0));
	Combination(Euro, ComEuro);
	//cout << ComEuro[Euro.size()][amount] << endl;

	cout << "三种货币（人民币、美元、欧元）中硬币构成各自货币里10元的组合数" << endl << endl;
	showConbination(ComYuan, ComDollar, ComEuro);

	system("pause");
	return 0;
}