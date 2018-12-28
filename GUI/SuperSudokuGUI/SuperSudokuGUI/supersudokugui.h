#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_supersudokugui.h"
#include "qlineedit.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qsignalmapper.h"
#include "qmessagebox.h"
#include "qtimer.h"
#include "qdatetime.h"
#include "qcolor.h"
#include "qscreen.h"

class SuperSudokuGUI : public QMainWindow
{
	Q_OBJECT

public:
	SuperSudokuGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::SuperSudokuGUIClass ui;
	QLabel *title;  //标题
	QLabel *usetime;  //使用时间
	QTimer *timer;  //使用时间
	QDateTime begin_time;  //开始时间，用于使用时间的计算
	QPushButton *sudoku[82];  //棋盘
	QPushButton *button[10];  //选项盘
	QPushButton *reset;  //清除
	QPushButton *newsudo;  //新数独
	QMenu *menu[5];  //菜单
	QAction *act[5];  //菜单
	QMenuBar *menuBar;  //菜单
	QStatusBar *status;  //菜单
	int tmp_select; //当前被选择的框
	int tmp_level; //当前游戏等级
	int the_num; //第几个数独
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
	char chessboard[10][10];  //数独终局盘
	char tmp_chessboard[10][10];  //当前数独
	int column[10], row[10], sub[10]; //判断合法
	int empty_num;  //剩余空数
	bool wrong[82];   //填错的位置
	void Create(int num = 1);  //创建数独
	void GetDig(); //挖空
	void InitBoard(); //将数独终局显示在界面上
	void recover();  //颜色恢复
	double factorx, factory;
	double s;
	int screen_width;
	int screen_height;
	void resetGrid(QWidget *widget);

private slots:
	void SelectSudoku(int tmp);  //选择数独框
	void SetSudoku(int tmp);  //填数
	void Reset();  //清零
	void NewGame();  //新游戏
	void level_1();  //初级
	void level_2();  //中级
	void level_3();  //高级
	void timeUpdate();  //时间
};
