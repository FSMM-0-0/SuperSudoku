#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define SIZE 10

class Board
{
private:
	int chessboard[SIZE][SIZE];  //�����վ���
	int num;  //�����վ�����
	//����ģ��
	char modle[11][11] = { "0",
		"0abcdefghi",
		"0defghiabc",
		"0ghiabcdef",
		"0bcaefdhig",
		"0efdhigbca",
		"0higbcaefd",
		"0cabfdeigh",
		"0fdeighcab",
		"0ighcabfde"
	};    
	void Output(int ord[SIZE], int firstrow[SIZE]); //�����վ����
	void Getpuzzle(); //���ɺ��ո��puzzle
	bool Create_exchange(int ord[SIZE], int firstrow[SIZE]); //�����վ��н���
public:
	void Create(); //���������վ�
	Board(int n = 0) : num(n) {} 
};

#endif // !__GENERATOR_H__

