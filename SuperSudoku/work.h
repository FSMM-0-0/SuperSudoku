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
		1:输入只有-c，没有终局个数
		2:终局个数含有其他非数字字符
		3:输入终局个数大于1000000
		4:终局数量为0
		5:生成终局命令合法
		6:没有输入求解数独文件路径
		7:求解数独文件路径不合法
		8:求解数独命令合法
		9:命令参数有误
*/
extern int test_input_flag; //用于单元测试输入是否正确

int str2int(char *s); //字符串转数字
void work(char *argv[]); //main函数

#endif //!__WORK_H_