//-----------------------------------------------------------------
// AboutWindow File
// C++ Source - AboutWindow.cpp - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "aboutwindow.h"
#include "ui_aboutwindow.h"

//-----------------------------------------------------------------
// AboutWindow methods
//-----------------------------------------------------------------
AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
