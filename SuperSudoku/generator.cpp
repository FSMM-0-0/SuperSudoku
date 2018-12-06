#include "generator.h"
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdio>

const int stuID = 9;
int idx[] = { 1, 4, 7 };

extern FILE *fp;
extern FILE *puzzle_fp;

/*
@Author:ZhuJingjing
@Description:递归生成数独终局
@Prameter:第k个小矩阵的第tmp个位置
@Return:
@Date:208-12-3
*/
void Board::Create(int k, int tmp)
{
	if (!num) return;
	if (k == 10) {
		if (num) {
			num--;
			Output();
		}
		else return;
	}

	//计算当前填充格的下标
	int i = idx[(k - 1) / 3] + (tmp - 1) / 3;
	int j = idx[(k - 1) % 3] + (tmp - 1) % 3;

	//从1到9遍历填充
	if (k == 1 && tmp == 1) {
		chessboard[i][j] = stuID;
		int shift = stuID - 1;
		sub[k] |= 1 << shift;
		row[i] |= 1 << shift;
		column[j] |= 1 << shift;
		Create(k, tmp + 1);
	}
	else {
		for (int dig = 1; dig <= 9; dig++) {
			//分别对小矩阵、行、列进行合法判断
			int shift = dig - 1;
			if (!((sub[k] >> shift) & 1) && !((row[i] >> shift) & 1) && !((column[j] >> shift) & 1)) {
				chessboard[i][j] = dig;

				sub[k] |= 1 << shift;
				row[i] |= 1 << shift;
				column[j] |= 1 << shift;

				if (tmp == 9) Create(k + 1, 1);
				else Create(k, tmp + 1);

				sub[k] ^= 1 << shift;
				row[i] ^= 1 << shift;
				column[j] ^= 1 << shift;
			}
		}

	}

}

Board::Board(int n)
{
	num = n;
	memset(chessboard, 0, sizeof(chessboard));
	memset(column, 0, sizeof(column));
	memset(row, 0, sizeof(row));
	memset(sub, 0, sizeof(sub));
}

/*
@Author:ZhuJingjing
@Description:输出数独终局
@Prameter:
@Return:
@Date:208-12-3
*/
void Board::Output()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d%c", chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(fp, "\n");

	Getpuzzle();
}

/*
@Author:ZhuJingjing
@Description:生成并输出quzzle
@Prameter:
@Return:
@Date:208-12-3
*/
void Board::Getpuzzle()
{
	int empty[SIZE];
	int tmp_chessboard[SIZE][SIZE];
	int sum = 0;

	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			tmp_chessboard[i][j] = chessboard[i][j];
		}
	}

	//随机生成每个3*3内空格数量
	while (sum < 30 || sum > 60) {
		sum = 0;

		empty[1] = rand() % 7 + 2; //随机生成2~8
		sum += empty[1];
		for (int i = 2; i <= 9; i++) {
			if (empty[i - 1] >= 5)  //上一个空格过多，生成2~4
				empty[i] = rand() % 3 + 2;  
			else                    //上一个空格过少，生成5~8
				empty[i] = rand() % 4 + 5;
			sum += empty[i];
		
		}
		
	}

	//在每个3*3内随机生成空格位置，置0
	int tmp, i, j;
	for (int k = 1; k <= 9; k++) {
		while (empty[k]) {
			tmp = rand() % 9 + 1;
			i = idx[(k - 1) / 3] + (tmp - 1) / 3;
			j = idx[(k - 1) % 3] + (tmp - 1) % 3;
			if (tmp_chessboard[i][j]) {
				tmp_chessboard[i][j] = 0;
				empty[k]--;
			}
		}
	}

	//输出quzzle到文件
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(puzzle_fp, "%d%c", tmp_chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(puzzle_fp, "\n");
}
