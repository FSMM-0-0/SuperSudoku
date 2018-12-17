#ifndef __WORK_H_
#define __WORK_H_
#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#pragma warning(disable:4996)

extern FILE *puzzle_fp;
extern FILE *generator_fp;
extern FILE *solution_fp;

/*
	test_input_flag
		1:����ֻ��-c��û���վָ���
		2:�վָ������������������ַ�
		3:�����վָ�������1000000
		4:�վ�����Ϊ0
		5:�����վ�����Ϸ�
		6:û��������������ļ�·��
		7:��������ļ�·�����Ϸ�
		8:�����������Ϸ�
		9:�����������
*/
extern int test_input_flag; //���ڵ�Ԫ���������Ƿ���ȷ

int str2int(char *s); //�ַ���ת����
void work(char *argv[]); //main����

#endif //!__WORK_H_