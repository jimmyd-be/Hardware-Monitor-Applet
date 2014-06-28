//-----------------------------------------------------------------
// TabWidget File
// C++ Header - TabWidget.h - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <QWidget>
 #include <QList>
#include "linewidget.h"
#include "WMI.h"

namespace Ui {

class TabWidget;
}

class MainWindow;


//-----------------------------------------------------------------
// TabWidget Class
//-----------------------------------------------------------------
class TabWidget : public QWidget
{
    Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    explicit TabWidget(WMI* wmi, MainWindow*, QWidget *parent = 0);

	//---------------------------
	// Destructor
	//---------------------------
    ~TabWidget();

	//---------------------------
	// General Methods
	//---------------------------
	
	void disableBrowse(bool);
	void setBackground(QString);
	void setLines(QVector<QString>);

	QString getbackground();
	QVector<QString> getLines();
	

public slots:
	//---------------------------
	// General Slots
	//---------------------------
    void addLine();
    void removeLine(LineWidget* line);
	void browseBackground();


private:
	// -------------------------
	// Datamembers
	// -------------------------
    Ui::TabWidget *ui;
    QList<LineWidget*> lineWidgets;
	WMI * wmi_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	TabWidget(const TabWidget& t);
	TabWidget& operator=(const TabWidget& t);
};