#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#define SIZE 10

class Generator
{
private:
	char chessboard[SIZE][SIZE];  //�����վ���
	char *out;
	int out_cnt;
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
	void Getchessboard(int ord[SIZE], char firstrow[SIZE]); //�����վ����
	bool Create_exchange(int ord[SIZE], char firstrow[SIZE]); //�����վ��н���
	void Getpuzzle(); //���ɺ��ո��puzzle
public:
	void Create(); //���������վ�
	void Output(); //��������վֵ��ļ�sudoku.txt
	Generator(int n = 0) : num(n), out_cnt(0) {} 
};

#endif // !__GENERATOR_H__

