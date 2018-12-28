#include "supersudokugui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	QApplication a(argc, argv);
	SuperSudokuGUI w;
	w.show();
	return a.exec();
}
