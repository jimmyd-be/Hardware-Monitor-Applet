#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//keyboardChanged(type);

	connect(ui.AddScreen_Button, SIGNAL(clicked()), this, SLOT(openScreenWizard()));
}

MainWindow::~MainWindow()
{
	
}

/*void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.statusBar->showMessage(tr("No Logitech keyboard found!!"));
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech monochrome (G15, G15s, G510) keyboard"));
	}
	else
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech color (G19, G19s) keyboard"));
	}

}*/

void MainWindow::openScreenWizard()
{
	CreateScreenWizard * wizard = new CreateScreenWizard();
	wizard->exec();
	
	delete wizard;
}
