#include <cstdio>
#include <cstring>
#include <malloc.h>
#include "solution.h"
#pragma warning(disable:4996)

extern FILE *solution_fp;

bool Puzzle::Read(char *path)
{
	FILE *puzzle_fp;
	int size = 0;

	puzzle_fp = fopen(path, "rb");
	if (puzzle_fp == NULL) {
		printf("��ȡ����ʧ��\n");
		return false;
	}

	fseek(puzzle_fp, 0, SEEK_END);
	size = ftell(puzzle_fp);
	rewind(puzzle_fp);

	read = new char[size];
	out = new char[size];

	fread(read, 1, size, puzzle_fp);
	fclose(puzzle_fp);
	return true;
}

void Puzzle::Init()
{
	memset(column, 0, sizeof(column));
	memset(row, 0, sizeof(row));
	memset(sub, 0, sizeof(sub));
	que.makeEmpty();
	que.push(Node(0, 0, 0));
	empty_num = 0;
}

/*
@Author:ZhuJingjing
@Description:��ʼ�����������
@Prameter:��r�У���r�е�����line[]
@Return:
@Date:2018-12-6
*/
void Puzzle::InitBoard()
{
	int len = strlen(read);
	for (int ch = 0; ch < len; ) { //���ζ�ȡÿһ���ַ�

		//��ʼ����ǰ����
		Init();

		//����һ������
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {

				puzzleboard[i][j] = read[ch];

				int k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
				if (puzzleboard[i][j] == '0') {
					que.push(Node(i, j, k));
					empty_num++;
				}
				else {
					int shift = puzzleboard[i][j] - '0' - 1;
					row[i] |= 1 << shift;
					column[j] |= 1 << shift;
					sub[k] |= 1 << shift;
				}

				ch++;
				while (!(read[ch] >= '0' && read[ch] <= '9') && ch < len) ch++;
				
			}
		}

		//��⵱ǰ����
		Solution();
		GetBoard();
		if (ch < len)
			out[out_cnt++] = '\n';
	}
}


/*
@Author:ZhuJingjing
@Description:��������������뻺��out
@Prameter:
@Return:
@Date:2018-12-11
*/
void Puzzle::GetBoard()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			out[out_cnt++] = puzzleboard[i][j];
			if (j == 9)
				out[out_cnt++] = '\n';
			else
				out[out_cnt++] = ' ';
		}
	}
}

void Puzzle::Output()
{
	if (fwrite(out, out_cnt, 1, solution_fp) != 1)
		printf("����������ʧ��\n");
	delete[] read;
	delete[] out;
}

//����1�ĸ���
int Num1(int x)
{
	int cot = 0;
	while (x) {
		x &= (x - 1);
		cot++;
	}
	return cot;
}

//�õ�0��λ��
int getNum(int x)
{
	int cot = 1;
	while (x & 1) {
		cot++;
		x >>= 1;
	}
	return cot;
}

/*
@Author:ZhuJingjing
@Description:dfs���
@Prameter:��tmp���ո񣬵�tmp���ո����Ϣnode[]
@Return:�Ƿ��ѵ����н�
@Date:2018-12-6
*/
bool Puzzle::dfs(int tmp, Node node[])
{
	if (!empty_num) return true;
	for (int i = 1; i <= node[tmp].maybe_num; i++) {
		int dig = node[tmp].maybe[i];
		int shift = dig - 1;

		if (!((sub[node[tmp].k] >> shift) & 1) && !((row[node[tmp].r] >> shift) & 1) && !((column[node[tmp].c] >> shift) & 1)) {
			puzzleboard[node[tmp].r][node[tmp].c] = dig + '0';
			column[node[tmp].c] |= 1 << shift;
			row[node[tmp].r] |= 1 << shift;
			sub[node[tmp].k] |= 1 << shift;
			empty_num--;

			if (dfs(tmp + 1, node)) return true;
			puzzleboard[node[tmp].r][node[tmp].c] = '0';
			sub[node[tmp].k] ^= 1 << shift;
			row[node[tmp].r] ^= 1 << shift;
			column[node[tmp].c] ^= 1 << shift;
			empty_num++;
		}
	
		
	}
	return false;
}

/*
@Author:ZhuJingjing
@Description:��������֣������Ψһ�⣬�ٵ���dfs
@Prameter:
@Return:
@Date:2018-12-6
*/
void Puzzle::Solution()
{
	bool flag = true;
	Node tmp(-1, -1, -1);
	while (empty_num) {
		//��дΨһ��ո�
		while (!que.isEmpty()) {
			tmp = que.front(); que.pop();

			if (tmp.k == 0) { //һ�ֱ��
				if (flag) {
					flag = false;
					que.push(tmp);
				}
				else
					break;  //��Ψһȷ������
			}
			else {
				int result = row[tmp.r] | column[tmp.c] | sub[tmp.k];
				if (Num1(result) == 8) {  //�ҵ�һ��Ψһȷ������
					int sure_num = getNum(result);
					int shift = sure_num - 1;
					puzzleboard[tmp.r][tmp.c] = sure_num + '0';

					flag = true;
					empty_num--;
					column[tmp.c] |= 1 << shift;
					row[tmp.r] |= 1 << shift;
					sub[tmp.k] |= 1 << shift;
				} 
				else {  //���¼������
					que.push(tmp);
				}
			}
		}

		if (!empty_num) break;
		//������з�Ψһ��ո��������֣�dfs���
		Node node[65];
		int cot = 0;
		while (!que.isEmpty()) {
			tmp = que.front(); que.pop();
			if (!tmp.r) continue;
			int result = row[tmp.r] | column[tmp.c] | sub[tmp.k];
			for (int i = 1; i <= 9; i++) {
				if ((result & (1 << (i - 1))) == 0) {
					tmp.maybe[++tmp.maybe_num] = i;
				}
			}

			node[++cot] = tmp;
		}
		dfs(1, node);
	}

}
