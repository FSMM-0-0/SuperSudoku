#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define SIZE 10

class Board
{
private:
	int chessboard[SIZE][SIZE];  //�����վ���
	int column[SIZE], row[SIZE], sub[SIZE]; //�жϺϷ�
	int num;  //�����վ�����
	void Output(); //�������
	void Getpuzzle(); //���ɺ��ո��puzzle
public:
	void Create(int k = 1, int tmp = 1);  //�����վ����ɺ���
	Board(int n = 0); //����


};

#endif // !__GENERATOR_H__

