#include "supersudokugui.h"

SuperSudokuGUI::SuperSudokuGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	the_num = 0;
	tmp_select = 0;
	tmp_level = 2;

	QScreen *screen = QGuiApplication::primaryScreen();
	QRect mm = screen->availableGeometry();
	screen_width = mm.width();
	screen_height = mm.height();
	factorx = screen_width / 1366.0; factory = screen_height / 768.0;
	//factorx = 1800.0 / 1366.0; factory = 500.0 / 768.0;
	//double h = 500.0 *630.0 / 768.0;
	double h = screen_height * 630.0 / 768.0;
	double w = h * 580.0 / 630.0;
	//this->resize(w, h);
	this->setFixedSize(w, h);

	//时间初始化
	QFont time_font;
	time_font.setFamily("Consolas");
	time_font.setWeight(65);
	s = 15.0 * screen_height / 768.0;
	//s = 13.0 * 500.0 / 768.0;
	time_font.setPixelSize(s);
	usetime = new QLabel(this);
	usetime->setGeometry(440, 25, 500, 80);	
	usetime->setScaledContents(true);
	resetGrid(usetime);
	usetime->setFont(time_font);
	timer = new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));

	//窗体初始化
	this->setWindowTitle(tr("SuperSudoku"));
	this->setAutoFillBackground(true);
	this->setStyleSheet("#SuperSudokuGUIClass{border-image: url(background.png)}");

	//菜单栏初始化
	status = new QStatusBar(this);

	menu[0] = new QMenu(QStringLiteral("新游戏"));
	act[0] = new QAction(QStringLiteral("初级"), this);
	menu[0]->addAction(act[0]);
	connect(act[0], SIGNAL(triggered()), this, SLOT(level_1()));
	act[1] = new QAction(QStringLiteral("中级"), this);
	menu[0]->addAction(act[1]);
	connect(act[1], SIGNAL(triggered()), this, SLOT(level_2()));
	act[2] = new QAction(QStringLiteral("高级"), this);
	menu[0]->addAction(act[2]);
	connect(act[2], SIGNAL(triggered()), this, SLOT(level_3()));

	menu[1] = new QMenu(QStringLiteral("保存"));
	menu[2] = new QMenu(QStringLiteral("打印"));
	menu[3] = new QMenu(QStringLiteral("帮助"));

	menuBar = new QMenuBar(this);
	menuBar->addMenu(menu[0]);
	menuBar->addMenu(menu[1]);
	menuBar->addMenu(menu[2]);
	menuBar->addMenu(menu[3]);
	double hh = 25.0 * h / 630.0;
	menuBar->setGeometry(0, 0, w, hh);

	//标题初始化
	QFont title_font;
	title_font.setFamily("Consolas");
	s = 35.0 * screen_height / 768.0;
	//s = 25.0 * 500.0 / 768.0;
	title_font.setPixelSize(s);
	title_font.setWeight(75);
	
	title = new QLabel(this);
	title->setGeometry(190, 10, 500, 80);
	resetGrid(title);
	title->setScaledContents(true);
	title->setFont(title_font);
	title->setText("SuperSudoku");

	//初始化数独盘
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {
			int tmp = (i - 1) * 9 + j;
			sudoku[tmp] = new QPushButton(this);
			int x = (tmp - 1) / 9, y = (tmp - 1) % 9;
			sudoku[tmp]->setGeometry((y + 1) * 45 + 40, (x + 1) * 45 + 35, 45, 45);
			resetGrid(sudoku[tmp]);
			sudoku[tmp]->setStyleSheet("border:none;");
		}
	}

	//选择键初始化
	QFont button_font;
	s = 30.0 * screen_height / 768.0;
	//s = 20.0 * 500.0 / 768.0;
	button_font.setPixelSize(s);
	button_font.setWeight(75);
	button_font.setFamily("Consolas");

	QSignalMapper *ansMapper = new QSignalMapper(this);
	for (int i = 1; i <= 9; i++) {
		button[i] = new QPushButton(this);
		QString str;
		str = QString::number(i);
		button[i]->setText(str);
		button[i]->setFont(button_font);
		button[i]->setGeometry(i * 60 - 35, 510, 50, 50);
		resetGrid(button[i]);
		button[i]->setFocus();
		ansMapper->setMapping(button[i], i);
		connect(button[i], SIGNAL(clicked()), ansMapper, SLOT(map()));
	}
	button[1]->setShortcut(Qt::Key_1);
	button[2]->setShortcut(Qt::Key_2);
	button[3]->setShortcut(Qt::Key_3);
	button[4]->setShortcut(Qt::Key_4);
	button[5]->setShortcut(Qt::Key_5);
	button[6]->setShortcut(Qt::Key_6);
	button[7]->setShortcut(Qt::Key_7);
	button[8]->setShortcut(Qt::Key_8);
	button[9]->setShortcut(Qt::Key_9);
	connect(ansMapper, SIGNAL(mapped(int)), this, SLOT(SetSudoku(int)));

	//清零和新建
	QFont button_font2;
	button_font2.setFamily("Consolas");
	button_font2.setWeight(70);
	s = 20.0 * screen_height / 768.0;
	//s = 15.0 * 500.0 / 768.0;
	button_font2.setPixelSize(s);

	newsudo = new QPushButton(this);
	newsudo->setText("New");
	newsudo->setGeometry(150, 575, 80, 35);
	resetGrid(newsudo);
	newsudo->setFont(button_font2);
	reset = new QPushButton(this);
	reset->setText("Reset");
	reset->setGeometry(350, 575, 80, 35);
	resetGrid(reset);
	reset->setFont(button_font2);
	connect(reset, SIGNAL(clicked()), this, SLOT(Reset()));
	connect(newsudo, SIGNAL(clicked()), this, SLOT(NewGame()));

	//数独盘生成
	Create(++the_num);
}

void SuperSudokuGUI::recover()
{
	if (tmp_select == 0) return;
	if (wrong[tmp_select]) return;
	int x = (tmp_select - 1) / 9, y = (tmp_select - 1) % 9;
	int color = x / 3 * 3 + y / 3 + 1;
	if (color & 1) {
		sudoku[tmp_select]->setStyleSheet("background-color: rgb(188, 210, 238);");
	}
	else {
		sudoku[tmp_select]->setStyleSheet("background-color: rgb(164, 211, 238);");
	}
}

void SuperSudokuGUI::resetGrid(QWidget * widget)
{
	double widgetX = widget->x();
	double widgetY = widget->y();
	double widgetWid = widget->width();
	double widgetHei = widget->height();
	double nWidgetY = (double)(widgetY*factory); 
	double nWidgetHei = (double)(widgetHei*factory); 
	double fx = 1.0 * nWidgetY / widgetY;
	double fw = 1.0 * nWidgetHei / widgetHei;
	double nWidgetX = (double)(widgetX*fx);
	double nWidgetWid = (double)(widgetWid*fw);
	//int nWidgetX = (int)(widgetX*factorx); 
	//int nWidgetWid = (int)(widgetWid*factorx); 
	widget->setGeometry(nWidgetX, nWidgetY, nWidgetWid, nWidgetHei);
}

void SuperSudokuGUI::SelectSudoku(int tmp)
{
	if (tmp == tmp_select) return;
	int i, j;
	i = (tmp - 1) / 9 + 1;
	j = (tmp - 1) % 9 + 1;
	if (chessboard[i][j] != '0') return;
	//设置选中色
	if (!wrong[tmp]) {
		sudoku[tmp]->setStyleSheet("background-color: rgb(255, 240, 245);");
	}
	//上一个选中者恢复颜色
	recover();
	tmp_select = tmp;
}

void SuperSudokuGUI::Create(int num)
{
	tmp_select = 0;
	empty_num = 0;
	memset(column, 0, sizeof(column));
	memset(row, 0, sizeof(row));
	memset(sub, 0, sizeof(sub));
	memset(wrong, false, sizeof(wrong));

	//学号(2+6)%9+1=9
	char firstrow[10] = { "912345678" };
	int ord[10];
	do {
		num--;
		if (!num) {
			for (int i = 1; i <= 9; i++) {
				for (int j = 1; j <= 9; j++) {
					chessboard[i][j] = firstrow[modle[i][j] - 'a'];
				}
			}
			GetDig();
			return;
		}
	} while (std::next_permutation(firstrow + 1, firstrow + 9));
}

void SuperSudokuGUI::GetDig()
{
	int empty[10];
	int sum = 0;

	//根据等级，随机生成每个3*3内空格数量
	if (tmp_level == 2) {
		while (sum < 30 || sum > 60) {
			sum = 0;
			empty[1] = rand() % 7 + 2; //随机生成2~8
			sum += empty[1];
			for (int i = 2; i <= 9; i++) {
				if (empty[i - 1] >= 6)  //上一个空格过多，生成3~6
					empty[i] = rand() % 4 + 3;
				else                    //上一个空格过少，生成6~8
					empty[i] = rand() % 3 + 6;
				sum += empty[i];
			}
		}
	}
	else if (tmp_level == 1) {
		while (sum < 30 || sum > 50) {
			sum = 0;
			empty[1] = rand() % 5 + 2; //随机生成2~6
			sum += empty[1];
			for (int i = 2; i <= 9; i++) {
				if (empty[i - 1] >= 4)  //上一个空格过多，生成2~3
					empty[i] = rand() % 2 + 3;
				else                    //上一个空格过少，生成4~6
					empty[i] = rand() % 3 + 4;
				sum += empty[i];
			}
		}
	}
	else if (tmp_level == 3) {
		while (sum < 30 || sum > 60) {
			sum = 0;
			empty[1] = rand() % 5 + 4; //随机生成4~9
			sum += empty[1];
			for (int i = 2; i <= 9; i++) {
				if (empty[i - 1] >= 6)  //上一个空格过多，生成4~6
					empty[i] = rand() % 3 + 4;
				else                    //上一个空格过少，生成6~9
					empty[i] = rand() % 4 + 6;
				sum += empty[i];
			}
		}
	}

	//在每个3*3内随机生成空格位置，置0
	int tmp, i, j;
	int idx[] = { 1, 4, 7 };
	for (int k = 1; k <= 9; k++) {
		while (empty[k]) {
			tmp = rand() % 9 + 1;
			i = idx[(k - 1) / 3] + (tmp - 1) / 3;
			j = idx[(k - 1) % 3] + (tmp - 1) % 3;
			if (chessboard[i][j] != '0') {
				chessboard[i][j] = '0';
				empty[k]--;
			}
		}
	}

	InitBoard();
}

void SuperSudokuGUI::InitBoard()
{
	QFont sudoku_bound_font;
	sudoku_bound_font.setFamily("Microsoft JhengHei");
	sudoku_bound_font.setWeight(65);
	s = 30.0 * screen_height / 768.0;
	//s = 25.0 * 500.0 / 768.0;
	sudoku_bound_font.setPixelSize(s);
	QFont sudoku_light_font;
	sudoku_light_font.setFamily("MV Boli");
	//sudoku_light_font.setFamily("French Script MT");
	sudoku_light_font.setWeight(45);
	s = 25.0 * screen_height / 768.0;
	//s = 30.0 * 500.0 / 768.0;
	sudoku_light_font.setPixelSize(s);

	QSignalMapper *sudoMapper = new QSignalMapper(this);
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= 9; j++) {

			tmp_chessboard[i][j] = chessboard[i][j];

			int tmp = (i - 1) * 9 + j;
			int x = (tmp - 1) / 9, y = (tmp - 1) % 9;
			int color = x / 3 * 3 + y / 3 + 1;
			if (color & 1) {
				sudoku[tmp]->setStyleSheet("background-color: rgb(188, 210, 238);");
			}
			else {
				sudoku[tmp]->setStyleSheet("background-color: rgb(164, 211, 238);");
			}

			if (chessboard[i][j] == '0') {
				sudoku[tmp]->setText("");
				sudoku[tmp]->setFont(sudoku_light_font);
				empty_num++;
			}
			else {
				QString str = QString(chessboard[i][j]);
				sudoku[tmp]->setText(str);
				sudoku[tmp]->setFont(sudoku_bound_font);
				int shift = chessboard[i][j] - '0' - 1;
				int k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
				row[i] |= 1 << shift;
				column[j] |= 1 << shift;
				sub[k] |= 1 << shift;
			}
			sudoMapper->setMapping(sudoku[tmp], tmp);
			connect(sudoku[tmp], SIGNAL(clicked()), sudoMapper, SLOT(map()));
		}
	}
	connect(sudoMapper, SIGNAL(mapped(int)), this, SLOT(SelectSudoku(int)));

	begin_time = QDateTime::currentDateTime();
}

void SuperSudokuGUI::SetSudoku(int tmp)
{
	if (tmp_select == 0) return;

	//当前选中者的坐标
	int i, j, k;
	i = (tmp_select - 1) / 9 + 1; 
	j = (tmp_select - 1) % 9 + 1;
	k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;

	//已经填过合法数，清除
	if (tmp_chessboard[i][j] != '0') {
		int ss = tmp_chessboard[i][j] - '0' - 1;
		sub[k] &= ~(1 << ss);
		row[i] &= ~(1 << ss);
		column[j] &= ~(1 << ss);
		empty_num++;
		tmp_chessboard[i][j] = '0';
	}

	QString str;
	str = QString::number(tmp);
	sudoku[tmp_select]->setText(str);

	int shift = tmp - 1;
	if (((sub[k] >> shift) & 1) || ((row[i] >> shift) & 1) || ((column[j] >> shift) & 1)) {
		sudoku[tmp_select]->setStyleSheet("background-color: rgb(255, 99, 71);");
		wrong[tmp_select] = true;
	}
	else {
		tmp_chessboard[i][j] = tmp + '0';
		column[j] |= 1 << shift;
		row[i] |= 1 << shift;
		sub[k] |= 1 << shift;
		empty_num--;
		wrong[tmp_select] = false;
		recover();
	}

	if (!empty_num) {
		QMessageBox message(QMessageBox::NoIcon, "", "\n     Success!      ");
		message.setIconPixmap(QPixmap("message.png"));
		if (message.exec() == QMessageBox::Ok) {
			Create(++the_num);
		}
	}

}

void SuperSudokuGUI::Reset()
{
	if (tmp_select == 0) return;
	
	if (!wrong[tmp_select]) {
		int i, j, k;
		i = (tmp_select - 1) / 9 + 1;
		j = (tmp_select - 1) % 9 + 1;
		k = (i - 1) / 3 * 3 + (j - 1) / 3 + 1;
		int shift = tmp_chessboard[i][j] - '0' - 1;
		sub[k] &= ~(1 << shift);
		row[i] &= ~(1 << shift);
		column[j] &= ~(1 << shift);
		empty_num++;
	}

	sudoku[tmp_select]->setText("");
	if (wrong[tmp_select]) wrong[tmp_select] = false;
	recover();

}

void SuperSudokuGUI::NewGame()
{
	Create(++the_num);
}

void SuperSudokuGUI::level_1()
{
	tmp_level = 1;
	Create(++the_num);
}

void SuperSudokuGUI::level_2()
{
	tmp_level = 2;
	Create(++the_num);
}

void SuperSudokuGUI::level_3()
{
	tmp_level = 3;
	Create(++the_num);
}

void SuperSudokuGUI::timeUpdate()
{
	QDateTime end_time = QDateTime::currentDateTime();
	QTime m_time;
	m_time.setHMS(0, 0, 0, 0);
	QString str = QStringLiteral("用时 ");
	str += m_time.addSecs(begin_time.secsTo(end_time)).toString("hh:mm:ss");
	usetime->setText(str);
}
