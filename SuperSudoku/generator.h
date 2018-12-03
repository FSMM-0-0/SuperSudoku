#ifndef __GENERATOR_H__
#define __GENERATOR_H__

const int SIZE = 10;

class Board
{
private:
	int chessboard[SIZE][SIZE];  //数独终局盘
	int column[SIZE], row[SIZE], sub[SIZE]; //判断合法
	int num;  //数独终局数量
	int Output(); //输出函数
public:
	void Create(int k = 1, int tmp = 1);  //数独终局生成函数
	Board(int n = 0); //构造


};

#endif // !__GENERATOR_H__

