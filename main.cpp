#include <QtWidgets/QApplication>
#include <external/QSingleApplication/SingleApplication.h>
#include "Controller.h"
#include <QTextCodec>

//Leak detector
//#include <vld.h>

int main(int argc, char *argv[])
{

	Controller * controller = nullptr;
#ifdef _WIN32
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	QApplication a(argc, argv);


	SingleApplication* singleApp = new SingleApplication();
#ifdef _WIN32
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

 #elif __linux__
    controller = new Controller(&a, singleApp);
    controller->openSettingsScreen();
#endif

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
#ifdef _WIN32
	CoUninitialize();
#endif
	return 0;
}
