#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SuperSudoku/generator.h"
#include "../SuperSudoku/solution.h"
#include "../SuperSudoku/work.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		//构造函数，生成测试数独
		UnitTest1()
		{
			FILE *test_fp = NULL;
			char test[200] =
			{ "9 0 0 3 5 4 6 7 8\n0 0 0 6 8 7 0 0 0\n6 0 8 9 0 0 3 4 0\n1 0 9 4 0 5 7 8 6\n4 5 0 7 0 0 0 2 9\n0 8 6 1 9 2 0 0 3\n0 9 0 5 4 3 0 0 0\n5 0 0 8 7 6 2 0 0\n0 6 0 2 0 0 0 3 0\n" };
			if ((test_fp = fopen("test.txt", "w+")) == NULL) {
				printf("创建数独测试文件失败\n");
			}
			else {
				if (fwrite(test, 200, 1, test_fp) != 1) {
					printf("测试输出文件失败\n");
				}
			}
			fclose(test_fp);
		}

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

		//对-c的输入错误测试
		TEST_METHOD(TestErrorInput1)
		{
			char *argv[3] = { NULL };
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-c";
			work(argv);
			Assert::AreEqual(test_input_flag, 1);
			argv[2] = "abc";
			work(argv);
			Assert::AreEqual(test_input_flag, 2);
			argv[2] = "9999999";
			work(argv);
			Assert::AreEqual(test_input_flag, 3);
			argv[2] = "0";
			work(argv);
			Assert::AreEqual(test_input_flag, 4);
		}

		//-c输入正确完成测试
		TEST_METHOD(TestRightInput2)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-c";
			argv[2] = "1000000";
			work(argv);
			Assert::AreEqual(test_input_flag, 5);
		}

		//-s输入错误测试
		TEST_METHOD(TestErrorInput3)
		{
			char *argv[3] = { NULL };
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-s";
			work(argv);
			Assert::AreEqual(test_input_flag, 6);
			argv[2] = "sol.txt";
			work(argv);
			Assert::AreEqual(test_input_flag, 7);
		}

		//-s输入正确完成测试
		TEST_METHOD(TestRightInput4)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-s";
			argv[2] = "test.txt";
			work(argv);
			Assert::AreEqual(test_input_flag, 8);
		}

		//输入错误格式测试
		TEST_METHOD(TestErrorInput5)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "a";
			argv[2] = "b";
			work(argv);
			Assert::AreEqual(test_input_flag, 9);
		}

		//是否生成了给定数量的数独
		TEST_METHOD(TestGenerator6)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-c";
			argv[2] = "6";
			work(argv);
			FILE *test_gen_fp = NULL;
			test_gen_fp = fopen("sudoku.txt", "rb");
			Assert::AreEqual(false, test_gen_fp == NULL);

			int cnt = 0, num = 0;
			char *read;
			fseek(test_gen_fp, 0, SEEK_END);
			int size = ftell(test_gen_fp);
			rewind(test_gen_fp);
			read = new char[size];
			fread(read, 1, size, test_gen_fp);
			fclose(test_gen_fp);
			for (int i = 0; i < size; i++) {
				if (read[i] >= '1' && read[i] <= '9') {
					cnt++;
				}
				else continue;
				if (cnt == 81) {
					num++;
					cnt = 0;
				}
			}
			Assert::AreEqual(num, 6);
		}

		bool check(int board[10][10])
		{
			int row[10], col[10], sub[10];
			for (int i = 0; i < 10; i++) row[i] = col[i] = sub[i] = 0;

			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					int k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
					int shift = board[i][j] - 1;
					if ((row[i] >> shift) & 1 || (col[j] >> shift) & 1 || (sub[k] >> shift) & 1)
						return false;
					row[i] |= 1 << shift;
					col[j] |= 1 << shift;
					sub[k] |= 1 << shift;
				}
			}
			return true;
		}

		//生成的数独是否合法
		TEST_METHOD(TestGenerator7)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-c";
			argv[2] = "6";
			work(argv);
			FILE *test_gen_fp = NULL;
			test_gen_fp = fopen("sudoku.txt", "rb");
			Assert::AreEqual(false, test_gen_fp == NULL);

			int cnt = 0, tmp = 1;
			char *read;
			int board[10][10];

			fseek(test_gen_fp, 0, SEEK_END);
			int size = ftell(test_gen_fp);
			rewind(test_gen_fp);
			read = new char[size];
			fread(read, 1, size, test_gen_fp);
			fclose(test_gen_fp);

			bool flag = true;
			for (int i = 0; i < size; i++) {
				if (read[i] >= '1' && read[i] <= '9') {
					if (cnt == 9) {
						tmp++; cnt = 0;
					}
					board[tmp][++cnt] = read[i] - '0';
				}
				else {
					if (tmp == 9 && cnt == 9) {
						if (board[1][1] != 9)
							flag = false;
						if (!check(board))
							flag = false;
						tmp = 1; cnt = 0;
					}
				}
			}

			Assert::AreEqual(true, flag);
		}

		bool same(int x, int y, int board[10][10][10])
		{
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					if (board[x][i][j] != board[y][i][j]) return false;
				}
			}
			return true;
		}

		//生成的数独是否无重复
		TEST_METHOD(TestGenerator8)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-c";
			argv[2] = "6";
			work(argv);
			FILE *test_gen_fp = NULL;
			test_gen_fp = fopen("sudoku.txt", "rb");
			Assert::AreEqual(false, test_gen_fp == NULL);

			char *read;
			fseek(test_gen_fp, 0, SEEK_END);
			int size = ftell(test_gen_fp);
			rewind(test_gen_fp);
			read = new char[size];
			fread(read, 1, size, test_gen_fp);
			fclose(test_gen_fp);

			int cnt = 0, num = 0, tmp = 1;
			int board[10][10][10];
			bool flag = true;

			for (int i = 0; i < size; i++) {
				if (read[i] >= '1' && read[i] <= '9') {
					if (cnt == 9) {
						tmp++; cnt = 0;
					}
					board[num][tmp][++cnt] = read[i] - '0';
				}
				else {
					if (tmp == 9 && cnt == 9) {
						tmp = 1; cnt = 0; num++;
					}
				}
			}

			for (int i = 0; i < 6; i++) {
				for (int j = i + 1; j < 6; j++) {
					if (same(i, j, board)) flag = false;
				}
			}

			Assert::IsTrue(flag);
		}

		//判断求解的数独是否合法
		TEST_METHOD(TestSolution9)
		{
			int board[10][10];
			Puzzle puzzle;
			puzzle.Read("test.txt");
			puzzle.InitBoard();
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					board[i][j] = puzzle.puzzleboard[i][j] - '0';
				}
			}
			Assert::IsTrue(check(board));
		}

		//判断求解后的数独是否输出成功
		TEST_METHOD(TestGenerator10)
		{
			char *argv[3];
			argv[0] = "SuperSudoku.exe";
			argv[1] = "-s";
			argv[2] = "test.txt";
			work(argv);
			FILE *test_sol_fp = NULL;
			test_sol_fp = fopen("sudoku.txt", "rb");
			Assert::IsNotNull(test_sol_fp);
		}


	};
}