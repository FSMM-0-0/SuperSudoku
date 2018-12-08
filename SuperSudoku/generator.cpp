#include "generator.h"
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <string>

const int stuID = 9;
int idx[] = { 1, 4, 7 };

extern FILE *fp;
extern FILE *puzzle_fp;


//@Author:ZhuJingjing
//@Description:��������վ�
//@Prameter:�����������˳��ord, ��һ�е�ģ��ӳ���ϵ
//@Return:
//@Date:208-12-7
void Board::Output(int ord[2][SIZE], int firstrow[SIZE])
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			chessboard[i][j] = firstrow[modle[ord[1][i]][ord[0][j]] - 'a'];
		}
	}
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d%c", chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(fp, "\n");
	Getpuzzle();
}

//@Author:ZhuJingjing
//@Description:ģ��ӳ���ȫ����,����dfs��������,���������վ�
//@Prameter:
//@Return:
//@Date:208-12-7
void Board::Create()
{
	int firstrow[SIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int seq[SIZE] = { 1, 2, 3 ,4, 5, 6, 7, 8, 9};
	int ord[2][SIZE];
	do {
		memset(ord, 0, sizeof(ord));
		if (Create_dfs(1, seq, ord, firstrow)) break;
 	} while (std::next_permutation(firstrow + 1, firstrow + 9));
}

//@Author:ZhuJingjing
//@Description:dfs��������
//@Prameter:��ǰdfs����tmp������λ(��3��3),����˳��seq,�������˳��ord,ģ��ӳ���ϵfirstrow
//@Return:�Ƿ����������վ�
//@Date:208-12-7
bool Board::Create_dfs(int tmp, int seq[SIZE], int ord[2][SIZE], int firstrow[SIZE])
{
	if (tmp == 7) {
		num--;
		Output(ord, firstrow);
		if (!num) return true;
	}
	else if (tmp == 1 || tmp == 4) {
		do {
			for (int i = 0; i <= 2; i++)
				tmp == 1 ? ord[0][i] = seq[i] : ord[1][i] = seq[i];
			if (Create_dfs(tmp + 1, seq, ord, firstrow)) return true;
		} while (std::next_permutation(seq + 1, seq + 2));
	}
	else if (tmp == 2 || tmp == 5) {
		do {
			for (int i = 3; i <= 5; i++)
				tmp == 2 ? ord[0][i] = seq[i] : ord[1][i] = seq[i];
			if (Create_dfs(tmp + 1, seq, ord, firstrow)) return true;
		} while (std::next_permutation(seq + 3, seq + 5));
	}
	else if (tmp == 3 || tmp == 6) {
		do {
			for (int i = 6; i <= 8; i++)
				tmp == 3 ? ord[0][i] = seq[i] : ord[1][i] = seq[i];
			if (Create_dfs(tmp + 1, seq, ord, firstrow)) return true;
		} while (std::next_permutation(seq + 6, seq + 8));
	}
	return false;
}

/*
@Author:ZhuJingjing
@Description:���ɲ����quzzle
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

	//�������ÿ��3*3�ڿո�����
	while (sum < 30 || sum > 60) {
		sum = 0;

		empty[1] = rand() % 7 + 2; //�������2~8
		sum += empty[1];
		for (int i = 2; i <= 9; i++) {
			if (empty[i - 1] >= 5)  //��һ���ո���࣬����2~4
				empty[i] = rand() % 3 + 2;  
			else                    //��һ���ո���٣�����5~8
				empty[i] = rand() % 4 + 5;
			sum += empty[i];
		
		}
		
	}

	//��ÿ��3*3��������ɿո�λ�ã���0
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

	//���quzzle���ļ�
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(puzzle_fp, "%d%c", tmp_chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(puzzle_fp, "\n");
}
