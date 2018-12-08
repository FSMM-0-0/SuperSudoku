#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define SIZE 10

class Board
{
private:
	int chessboard[SIZE][SIZE];  //数独终局盘
	int num;  //数独终局数量
	//数独模板
	char modle[11][11] = { "0",
		"0abcdefghi",
		"0defghiabc",
		"0ghiabcdef",
		"0bcaefdhig",
		"0efdhigbca",
		"0higbcaefd",
		"0cabfdeigh",
		"0fdeighcab",
		"0ighcabfde"
	};    
	void Output(int ord[SIZE], int firstrow[SIZE]); //数独终局输出
	void Getpuzzle(); //生成含空格的puzzle
	bool Create_exchange(int ord[SIZE], int firstrow[SIZE]); //数独终局列交换
public:
	void Create(); //生成数独终局
	Board(int n = 0) : num(n) {} 
};

#endif // !__GENERATOR_H__

