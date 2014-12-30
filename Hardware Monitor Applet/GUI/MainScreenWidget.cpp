#include "MainScreenWidget.h"

#include "mainwindow.h"

MainScreenWidget::MainScreenWidget(MainWindow * mainWindow, Logitech * logitech, QString name, ScreenType type, bool active, QWidget *parent)
	: QWidget(parent), logitech_(logitech), mainWindow_(mainWindow)
{
	setupUi(this);

	ScreenName_Label->setText(name);
	ScreenType_Label->setText(Defines::translateScreenTypeEnum(type));

	if (active)
	{
		ScreenActive_Label->setText("Used");
		ScreenActive_Label->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
	}
	else
	{
		ScreenActive_Label->setText("Unused");
		ScreenActive_Label->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
	}

	QPalette p(palette());
	p.setColor(QPalette::Background, Qt::white);
	setAutoFillBackground(true);
	setPalette(p);

	connect(RemoveScreen_Button, SIGNAL(clicked()), this, SLOT(removePage()));
	connect(EditScreen_Button, SIGNAL(clicked()), this, SLOT(editpage()));

}

MainScreenWidget::~MainScreenWidget()
{
	
}

void MainScreenWidget::removePage()
{
	logitech_->deleteScreen(ScreenName_Label->text());

	Settings::getInstance()->saveSettings();

	mainWindow_->refreshPages();
}

void MainScreenWidget::editpage()
{
	CreateScreenWizard * wizard = new CreateScreenWizard(logitech_, ScreenName_Label->text());
	wizard->exec();

	delete wizard;

	Settings::getInstance()->saveSettings();

	mainWindow_->refreshPages();
}
