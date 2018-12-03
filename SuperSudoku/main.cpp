#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "generator.h"
#pragma warning(disable:4996)
using namespace std;

FILE *fp = NULL;

//判断输入数独数量大小n是否合法
int str2int(char s[])
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


	if (strcmp(argv[1], "-c") == 0) {
		int n = str2int(argv[2]);
		if (n >= 1) {
			fp = fopen("sudoku.txt", "w");
			if (NULL == fp) return -1;

			Board board(n);
			board.Create(1, 1);

			fclose(fp);
			fp = NULL;
			printf("生成数独终局成功\n");
		}
		else {
			printf("请输入正确的数独终局数量，范围是1≤N≤1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {

	}
	else {
		printf("请输入正确的命令参数\n");
	}


	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);
	return 0;
}