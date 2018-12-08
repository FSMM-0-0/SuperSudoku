#include <cstdio>
#include <cstring>
#include "solution.h"

extern FILE *solution_fp;


void Puzzle::Init()
{
	que.makeEmpty();
	que.push(Node(0, 0, 0));
	empty_num = 0;
	memset(puzzleboard, 0, sizeof(puzzleboard));
	memset(column, 0, sizeof(column));
	memset(row, 0, sizeof(row));
	memset(sub, 0, sizeof(sub));
}

/*
@Author:ZhuJingjing
@Description:初始化数独求解盘
@Prameter:第r行，第r行的内容line[]
@Return:
@Date:208-12-6
*/
void Puzzle::InitBoard(int r, char line[])
{
	if (r > 9) return;
	int len = 17, col = 0;

	for (int i = 0; i < len; i += 2) {
		puzzleboard[r][++col] = line[i] - '0';

		int k = (r - 1) / 3 * 3 + (col - 1) / 3 + 1;
		if (line[i] == '0') {
			que.push(Node(r, col, k));
			empty_num++;
		}
		else {
			int shift = puzzleboard[r][col] - 1;
			row[r] |= 1 << shift;
			column[col] |= 1 << shift;
			sub[k] |= 1 << shift;
		}
		
	}
}

void Puzzle::Output()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(solution_fp, "%d%c", puzzleboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
}

//返回1的个数
int Num1(int x)
{
	int cot = 0;
	while (x) {
		x &= (x - 1);
		cot++;
	}
	return cot;
}

//得到0的位置
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
@Description:dfs求解
@Prameter:第tmp个空格，第tmp个空格点信息node[]
@Return:是否搜到可行解
@Date:208-12-6
*/
bool Puzzle::dfs(int tmp, Node node[])
{
	if (!empty_num) return true;
	for (int i = 1; i <= node[tmp].maybe_num; i++) {
		int dig = node[tmp].maybe[i];
		int shift = dig - 1;

		if (!((sub[node[tmp].k] >> shift) & 1) && !((row[node[tmp].r] >> shift) & 1) && !((column[node[tmp].c] >> shift) & 1)) {
			puzzleboard[node[tmp].r][node[tmp].c] = dig;
			column[node[tmp].c] |= 1 << shift;
			row[node[tmp].r] |= 1 << shift;
			sub[node[tmp].k] |= 1 << shift;
			empty_num--;

			if (dfs(tmp + 1, node)) return true;
			puzzleboard[node[tmp].r][node[tmp].c] = 0;
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
@Description:求解数独局，先填充唯一解，再调用dfs
@Prameter:
@Return:
@Date:208-12-6
*/
bool Puzzle::Solution()
{
	bool flag = true;
	Node tmp(-1, -1, -1);
	while (empty_num) {
		////填写唯一解空格
		//while (!que.isEmpty()) {
		//	tmp = que.front(); que.pop();

		//	if (tmp.k == 0) { //一轮标记
		//		if (flag) {
		//			flag = false;
		//			que.push(tmp);
		//		}
		//		else
		//			break;  //无唯一确定方格
		//	}
		//	else {
		//		int result = row[tmp.r] | column[tmp.c] | sub[tmp.k];
		//		if (Num1(result) == 8) {  //找到一个唯一确定方格
		//			int sure_num = getNum(result);
		//			int shift = sure_num - 1;
		//			puzzleboard[tmp.r][tmp.c] = sure_num;

		//			flag = true;
		//			empty_num--;
		//			column[tmp.c] |= 1 << shift;
		//			row[tmp.r] |= 1 << shift;
		//			sub[tmp.k] |= 1 << shift;
		//		} 
		//		else {  //重新加入队列
		//			que.push(tmp);
		//		}
		//	}
		//}

		if (!empty_num) break;
		//求出所有非唯一解空格可填的数字，dfs求解
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
	return true;
}
