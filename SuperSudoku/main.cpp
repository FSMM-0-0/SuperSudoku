#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "generator.h"
#pragma warning(disable:4996)
using namespace std;

FILE *fp = NULL;

//�ж���������������Сn�Ƿ�Ϸ�
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
			printf("���������վֳɹ�\n");
		}
		else {
			printf("��������ȷ�������վ���������Χ��1��N��1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {

	}
	else {
		printf("��������ȷ���������\n");
	}


	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);
	return 0;
}