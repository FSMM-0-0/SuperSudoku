#include "CreateBoard.h"
#include <cstring>
#include <iostream>
#include <cstdio>

const int MAX = (1 << 9) - 1;
const int stuID = 9;
int idx[] = { 1, 4, 7 };
extern FILE *fp;

void Board::Create(int k, int tmp)
{
	if (!num) return;
	if (k == 10) {
		if (num) {
			num--;
			Output();
		}
		else return;
	}

	int i = idx[(k - 1) / 3] + (tmp - 1) / 3;
	int j = idx[(k - 1) % 3] + (tmp - 1) % 3;

	if (k == 1 && tmp == 1) {
		chessboard[i][j] = stuID;
		sub[k] |= 1 << (stuID - 1);
		row[i] |= 1 << (stuID - 1);
		column[j] |= 1 << (stuID - 1);
		Create(k, tmp + 1);
	}
	else {
		for (int dig = 1; dig <= 9; dig++) {
			if (!((sub[k] >> (dig - 1)) & 1) && !((row[i] >> (dig - 1)) & 1) && !((column[j] >> (dig - 1)) & 1)) {
				chessboard[i][j] = dig;

				sub[k] |= 1 << (dig - 1);
				row[i] |= 1 << (dig - 1);
				column[j] |= 1 << (dig - 1);

				if (tmp == 9) Create(k + 1, 1);
				else Create(k, tmp + 1);

				sub[k] ^= 1 << (dig - 1);
				row[i] ^= 1 << (dig - 1);
				column[j] ^= 1 << (dig - 1);
			}
		}

	}

}

Board::Board(int n)
{
	num = n;
	memset(chessboard, 0, sizeof(chessboard));
	memset(column, 0, sizeof(column));
	memset(row, 0, sizeof(row));
	memset(sub, 0, sizeof(sub));
}

int Board::Output()
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			fprintf(fp, "%d%c", chessboard[i][j], j == 9 ? '\n' : ' ');
		}
	}
	if (num) fprintf(fp, "\n");

	return 0;
}
