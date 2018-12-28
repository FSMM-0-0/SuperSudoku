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
	QLabel *title;  //����
	QLabel *usetime;  //ʹ��ʱ��
	QTimer *timer;  //ʹ��ʱ��
	QDateTime begin_time;  //��ʼʱ�䣬����ʹ��ʱ��ļ���
	QPushButton *sudoku[82];  //����
	QPushButton *button[10];  //ѡ����
	QPushButton *reset;  //���
	QPushButton *newsudo;  //������
	QMenu *menu[5];  //�˵�
	QAction *act[5];  //�˵�
	QMenuBar *menuBar;  //�˵�
	QStatusBar *status;  //�˵�
	int tmp_select; //��ǰ��ѡ��Ŀ�
	int tmp_level; //��ǰ��Ϸ�ȼ�
	int the_num; //�ڼ�������
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
	char chessboard[10][10];  //�����վ���
	char tmp_chessboard[10][10];  //��ǰ����
	int column[10], row[10], sub[10]; //�жϺϷ�
	int empty_num;  //ʣ�����
	bool wrong[82];   //����λ��
	void Create(int num = 1);  //��������
	void GetDig(); //�ڿ�
	void InitBoard(); //�������վ���ʾ�ڽ�����
	void recover();  //��ɫ�ָ�
	double factorx, factory;
	double s;
	int screen_width;
	int screen_height;
	void resetGrid(QWidget *widget);

private slots:
	void SelectSudoku(int tmp);  //ѡ��������
	void SetSudoku(int tmp);  //����
	void Reset();  //����
	void NewGame();  //����Ϸ
	void level_1();  //����
	void level_2();  //�м�
	void level_3();  //�߼�
	void timeUpdate();  //ʱ��
};
