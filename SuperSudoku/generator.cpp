#include "generator.h"
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <string>
#pragma warning(disable:4996)

int idx[] = { 1, 4, 7 };

extern FILE *puzzle_fp;
extern FILE *generator_fp;

void Generator::Output()
{
	if (!out_cnt) return;
	if (fwrite(out, out_cnt, 1, generator_fp) != 1)
		printf("输出数独终局失败\n");

	out_cnt = 0;
}

//@Author:ZhuJingjing
//@Description:输出数独终局
//@Prameter:交换后的行列顺序ord, 第一行的模板映射关系
//@Return:
//@Date:208-12-7
void Generator::Getchessboard(int ord[], char firstrow[])
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			chessboard[i][j] = firstrow[modle[i][ord[j - 1]] - 'a'];
		}
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			out[out_cnt++] = chessboard[i][j];
			if (out_cnt == MAXN) Output();
			if (j == 9) 
				out[out_cnt++] = '\n';
			else
				out[out_cnt++] = ' ';
			if (out_cnt == MAXN) Output();
		}
	}

	if (num) {
		out[out_cnt++] = '\n';
	}
	if (out_cnt == MAXN) Output();
	//Getpuzzle();
}

//@Author:Jingjing Zhu
//@Description:模板映射表全排列,调用exchange交换行列,生成数独终局
//@Prameter:
//@Return:
//@Date:208-12-7
void Generator::Create()
{
	char firstrow[SIZE] = { "912345678" };
	int ord[SIZE];
	do {
		if (Create_exchange(ord, firstrow)) break;
 	} while (std::next_permutation(firstrow + 1, firstrow + 9));
}


//@Author:ZhuJingjing
//@Description:交换行列生成数独终局
//@Prameter:交换后的顺序ord,模板映射关系firstrow
//@Return:是否生成所有终局
//@Date:208-12-8
bool Generator::Create_exchange(int ord[], char firstrow[])
{
	char per1[2][4] = { "123", "132" },
		per2[6][4] = { "456", "465", "546", "564", "645", "654" },
		per3[6][4] = { "789", "798", "879", "897", "978", "987" };
	for (int i = 0; i < 2; i++) {
		for (int ii = 0; ii < 3; ii++) ord[ii] = per1[i][ii] - '0';

		for (int j = 0; j < 6; j++) {
			for (int jj = 0; jj < 3; jj++) ord[jj + 3] = per2[j][jj] - '0';

			for (int k = 0; k < 6; k++) {
				for (int kk = 0; kk < 3; kk++) ord[kk + 6] = per3[k][kk] - '0';

				num--;
				Getchessboard(ord, firstrow);
				if (!num)
					return true;
			}
		}
	}
	return false;
}


/*
@Author:ZhuJingjing
@Description:生成并输出quzzle，用于求解测试
@Prameter:
@Return:
@Date:208-12-3
*/
void Generator::Getpuzzle()
{
	int empty[SIZE];
	char tmp_chessboard[SIZE][SIZE];
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
				tmp_chessboard[i][j] = '0';
				empty[k]--;
			}
		}
	}

	//输出quzzle到文件
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(puzzle_fp, "%c%c", tmp_chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(puzzle_fp, "\n");
}
