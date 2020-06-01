#ifndef MAINSCREENWIDGET_H
#define MAINSCREENWIDGET_H
#include "../Defines.h"
#include "ui_MainScreenWidget.h"
#include "../Logitech.h"

#include "CreateScreenWizard.h"


class MainScreenWidget :
	public QWidget, private Ui_MainScreenWidget
{
	Q_OBJECT

public:
    MainScreenWidget(Logitech * logitech, QString name, ScreenType type, bool active, QWidget *parent = 0);
	virtual ~MainScreenWidget();

signals:
    void refreshMainWindow();

private slots:
	void removePage();
	void editpage();
	

private:
	Logitech * logitech_;



};
#endif
