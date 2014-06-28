//-----------------------------------------------------------------
// LineWidget File
// C++ Header - LineWidget.h - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <QWidget>
#include "datawindow.h"
#include "WMI.h"

namespace Ui {
class LineWidget;
}

class TabWidget;

//-----------------------------------------------------------------
// LineWidget Class
//-----------------------------------------------------------------
class LineWidget : public QWidget
{
    Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    explicit LineWidget(WMI* wmi, TabWidget*, int id, QWidget *parent = 0);

	//---------------------------
	// Destructor
	//---------------------------
    ~LineWidget();

	//---------------------------
	// General Methods
	//---------------------------
    void setId(int id);
	void setText(QString);
    int getId();
	QString getText();

private slots:
//---------------------------
// General Slots
//---------------------------
    void removeLine();
	void openDataWindow();

private:
	// -------------------------
	// Datamembers
	// -------------------------
    Ui::LineWidget *ui;
    int id_;
    TabWidget * tabWidget_;
	WMI * wmi_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	LineWidget(const LineWidget& t);
	LineWidget& operator=(const LineWidget& t);
};

