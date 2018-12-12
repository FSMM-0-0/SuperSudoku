#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "generator.h"
#include "solution.h"
#pragma warning(disable:4996)
using namespace std;

FILE *puzzle_fp = NULL;
FILE *generator_fp = NULL;
FILE *solution_fp = NULL;

//判断输入数独数量大小n是否合法
int str2int(char *s)
{
	int len = strlen(s);
	int x = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			x = x * 10 + s[i] - '0';
		}
		else return -1;
		if (x > 1000000) return -1;
	}
	return x;
}

int main(int argc, char *argv[])
{
	long _begin_time = clock();
	//srand((unsigned)time(NULL));

	if (strcmp(argv[1], "-c") == 0) {
		int n = 0;
		char *number = NULL;
		number = argv[2];
		if (number == NULL){
			printf("请输入数独终局个数\n");
			return -1;
		}
		n = str2int(number);
		if (n >= 1) {

			//if ((puzzle_fp = fopen("puzzle.txt", "w+")) == NULL) {
			//	printf("创建puzzle.txt文件失败\n");
			//	return -1;
			//}

			if ((generator_fp = fopen("sudoku.txt", "w+")) == NULL) {
				printf("创建数独终局文件失败\n");
				return -1;
			}

			Generator board(n);
			board.Create();
			board.Output();

			fclose(generator_fp);
			printf("数独终局生成成功\n");

			//fclose(puzzle_fp);
			//puzzle_fp = NULL;

		}
		else {
			printf("请输入正确的数独终局数量，范围是1≤N≤1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {
		char *path = NULL;
		path = argv[2];
		if (path == NULL) {
			printf("请输入数独文件\n");
			return -1;
		}

		if ((solution_fp = fopen("sudoku.txt", "w+")) == NULL) {
			printf("创建数独求解文件失败\n");
			return -1;
		}

		Puzzle puzzle;
		if (!puzzle.Read(path)) {
			return -1;
		}
		puzzle.InitBoard();
		puzzle.Output();

		fclose(solution_fp);
		printf("数独求解成功\n");

	}
	else {
		printf("请输入正确的命令参数\n");
	}


	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);




	return 0;
}