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
	void Output(int ord[2][SIZE], int firstrow[SIZE]); //数独终局输出
	bool Create_dfs(int tmp, int seq[SIZE], int ord[2][SIZE], int firstrow[SIZE]); //数独终局交换生成
	void Getpuzzle(); //生成含空格的puzzle
public:
	void Create(); //生成数独终局
	Board(int n = 0) : num(n) {} //构造
};

#endif // !__GENERATOR_H__

