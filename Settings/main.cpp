#include "mainwindow.h"
#include <QApplication>
#include "WMI.h"

int main(int argc, char *argv[])
{
	WMI* wmi = new WMI();
    QApplication a(argc, argv);
	MainWindow w(wmi);
    w.show();

    return a.exec();
}