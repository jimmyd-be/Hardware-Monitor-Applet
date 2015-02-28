#include <QtWidgets/QApplication>
#include <external\QSingleApplication\singleapplication.h>
#include "Controller.h"
#include <QTextCodec>

#include <GUI\mainwindow.h>

int main(int argc, char *argv[])
{
	Controller * controller = nullptr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	QApplication a(argc, argv);

	SingleApplication* singleApp = new SingleApplication();

	if (singleApp->isRunning())
	{
		if (QApplication::arguments().size() > 1)
		{
			singleApp->sendMessage(QApplication::arguments().at(1));
			return 0;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		controller = new Controller(&a, singleApp);

		if (QApplication::arguments().size() > 1 && QApplication::arguments().at(1) == "Settings")
		{
			controller->openSettingsScreen();
		}
	}

	a.exec();

	Data::removeInstance();

	if (controller != nullptr)
	{
		delete controller;
		controller = nullptr;
	}

	if (singleApp != nullptr)
	{
		delete singleApp;
		singleApp = nullptr;
	}

	CoUninitialize();

	return 0;
}