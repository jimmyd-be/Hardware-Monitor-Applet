#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "tabwidget.h"
#include "WMI.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(WMI* wmi, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addNewPage();
    void removePage();

private:
    Ui::MainWindow *ui;

    QPushButton* addPageButton;
	WMI * wmi_;
};

#endif // MAINWINDOW_H
