#ifndef __CREATEBOARD_H__
#define __CREATEBOARD_H__

const int SIZE = 10;

class Board
{
private:
	int chessboard[SIZE][SIZE];
	int column[SIZE], row[SIZE], sub[SIZE];
	int num;
	int Output();
public:
	void Create(int k = 1, int tmp = 1);
	Board(int n = 0);


};

#endif // !__CREATEBOARD_H__

