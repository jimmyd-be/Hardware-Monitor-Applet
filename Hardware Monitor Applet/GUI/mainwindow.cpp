#include "mainwindow.h"

MainWindow::MainWindow(KeyboardTypes type, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	keyboardChanged(type);
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.keyboardLabel->setText("No Logitech keyboard found!!");
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.keyboardLabel->setText("Logitech monochrome (G15, G15s, G510) keyboard found!!");

		ui.backgroundBrowseButton->hide();
		ui.backgroundLabel->hide();
		ui.backgroundLine->hide();
	}
	else
	{
		ui.keyboardLabel->setText("Logitech color (G19, G19s) keyboard found!!");
		
		ui.backgroundBrowseButton->show();
		ui.backgroundLabel->show();
		ui.backgroundLine->show();
	}
}