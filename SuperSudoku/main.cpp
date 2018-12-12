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

//�ж���������������Сn�Ƿ�Ϸ�
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
			printf("�����������վָ���\n");
			return -1;
		}
		n = str2int(number);
		if (n >= 1) {

			//if ((puzzle_fp = fopen("puzzle.txt", "w+")) == NULL) {
			//	printf("����puzzle.txt�ļ�ʧ��\n");
			//	return -1;
			//}

			if ((generator_fp = fopen("sudoku.txt", "w+")) == NULL) {
				printf("���������վ��ļ�ʧ��\n");
				return -1;
			}

			Generator board(n);
			board.Create();
			board.Output();

			fclose(generator_fp);
			printf("�����վ����ɳɹ�\n");

			//fclose(puzzle_fp);
			//puzzle_fp = NULL;

		}
		else {
			printf("��������ȷ�������վ���������Χ��1��N��1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {
		char *path = NULL;
		path = argv[2];
		if (path == NULL) {
			printf("�����������ļ�\n");
			return -1;
		}

		if ((solution_fp = fopen("sudoku.txt", "w+")) == NULL) {
			printf("������������ļ�ʧ��\n");
			return -1;
		}

		Puzzle puzzle;
		if (!puzzle.Read(path)) {
			return -1;
		}
		puzzle.InitBoard();
		puzzle.Output();

		fclose(solution_fp);
		printf("�������ɹ�\n");

	}
	else {
		printf("��������ȷ���������\n");
	}


	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);




	return 0;
}