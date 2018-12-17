#include "work.h"
#include "generator.h"
#include "solution.h"

FILE *puzzle_fp = NULL;
FILE *generator_fp = NULL;
FILE *solution_fp = NULL;

int test_input_flag = 0;

//�ж���������������Сn�Ƿ�Ϸ�
int str2int(char *s)
{
	int len = strlen(s);
	int x = 0;
	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			x = x * 10 + s[i] - '0';
		}
		else {
			test_input_flag = 2; //�����վָ������������ַ�
			return -1;
		}
		if (x > 1000000) {
			test_input_flag = 3; //�����վָ�������1000000
			return -1;
		}
	}
	return x;
}

void work(char *argv[])
{
	if (strcmp(argv[1], "-c") == 0) {
		int n = 0;
		char *number = NULL;
		number = argv[2];
		if (number == NULL) {
			test_input_flag = 1;  //����ֻ��-c��û�������վָ���
			printf("�����������վָ���\n");
			return;
		}
		n = str2int(number);
		if (n >= 1) {
			test_input_flag = 5; //�����վ�����Ϸ�
			//if ((puzzle_fp = fopen("puzzle.txt", "w+")) == NULL) {
			//	printf("����puzzle.txt�ļ�ʧ��\n");
			//	return -1;
			//}

			if ((generator_fp = fopen("sudoku.txt", "w+")) == NULL) {
				printf("���������վ��ļ�ʧ��\n");
				return;
			}

			Generator board(n);
			board.Create();
			board.Output();

			fclose(generator_fp);
			printf("�����վ����ɳɹ�\n");

			//fclose(puzzle_fp);
			//puzzle_fp = NULL;

		}
		else if (n == 0){
			test_input_flag = 4; //�վ�����Ϊ0
			printf("��������ȷ�������վ���������Χ��1��N��1000000\n");
		}
	}
	else if (strcmp(argv[1], "-s") == 0) {
		char *path = NULL;
		path = argv[2];
		if (path == NULL) {
			test_input_flag = 6; //û��������������ļ�·��
			printf("�����������ļ�\n");
			return;
		}

		if ((solution_fp = fopen("sudoku.txt", "w+")) == NULL) {
			printf("������������ļ�ʧ��\n");
			return;
		}

		Puzzle puzzle;
		if (!puzzle.Read(path)) {
			test_input_flag = 7; //��������ļ�·�����Ϸ�
			return;
		}
		puzzle.InitBoard();
		puzzle.Output();

		fclose(solution_fp);
		printf("�������ɹ�\n");
		test_input_flag = 8; //�����������Ϸ�

	}
	else {
		test_input_flag = 9; //�����������
		printf("��������ȷ���������\n");
	}
}