#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include "generator.h"
#include "solution.h"
#include "test.h"
#pragma warning(disable:4996)
using namespace std;

FILE *fp = NULL;
FILE *puzzle_fp = NULL;
FILE *solution_fp = NULL;
const int MAXN = 1000006;
Puzzle puzzle;


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
	srand((unsigned)time(NULL));

	if (strcmp(argv[1], "-c") == 0) {
		int n = str2int(argv[2]);
		if (n >= 1) {
			fp = fopen("sudoku.txt", "w");
			puzzle_fp = fopen("puzzle.txt", "w");
			
			if (fp == NULL) {
				printf("����sudoku.txt�ļ�ʧ��\n");
				return -1;
			}
			if (puzzle_fp == NULL) {
				printf("����puzzle.txt�ļ�ʧ��\n");
				return -1;
			}

			Board board(n);
			board.Create();

			fclose(fp);
			fclose(puzzle_fp);
			fp = NULL;
			puzzle_fp = NULL;
			printf("���������վֳɹ�\n");
		}
		else {
			printf("��������ȷ�������վ���������Χ��1��N��1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {
		char *path = argv[2];
		puzzle_fp = fopen(path, "r");
		if (puzzle_fp == NULL) {
			printf("��puzzle.txt�ļ�ʧ��\n");
			return -1;
		}
		solution_fp = fopen("sudoku.txt", "w");
		if (solution_fp == NULL) {
			printf("����sudoku.txt�ļ�ʧ��\n");
			return -1;
		}

		char line[100];
		memset(line, 0, sizeof(line));
		int puzzle_num = 1;
		int row = 1;

		bool first = false;

		puzzle.Init();
		while (!feof(puzzle_fp)) {
			fgets(line, 1000000, puzzle_fp);
			if (line[0] == '\n') {
				first = true;
				//puzzle.Solution();
				//fprintf(solution_fp, "%d:\n", ++cnt);
				//puzzle.Output();
				//fprintf(solution_fp, "\n");
				//row = 1;
				//puzzle.Init();
			}
			else {	
				if (first) {
					first = false;
					puzzle.Solution();
					puzzle.Output();
					fprintf(solution_fp, "\n");
					row = 1;
					puzzle.Init();
				}
				puzzle.InitBoard(row, line);
				row++;
			}
		}
		puzzle.Solution();
		puzzle.Output();

		fclose(puzzle_fp);
		puzzle_fp = NULL;
		printf("�����̶�ȡ�ɹ�\n");

		fclose(solution_fp);
		solution_fp = NULL;
		printf("�������ɹ�\n");
	}
	else {
		printf("��������ȷ���������\n");
	}


	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);




	return 0;
}