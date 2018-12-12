#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define SIZE 10
#define MAXN 1000000
extern char out[MAXN];
extern int out_cnt;

class Generator
{
private:
	char chessboard[SIZE][SIZE];  //数独终局盘
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
	void Getchessboard(int ord[SIZE], char firstrow[SIZE]); //数独终局输出
	bool Create_exchange(int ord[SIZE], char firstrow[SIZE]); //数独终局列交换
	void Getpuzzle(); //生成含空格的puzzle
public:
	void Create(); //生成数独终局
	void Output(); //输出数独终局到文件sudoku.txt
	Generator(int n = 0) : num(n) {} 
};

#endif // !__GENERATOR_H__

