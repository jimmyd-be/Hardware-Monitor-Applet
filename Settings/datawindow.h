//-----------------------------------------------------------------
// DataWindow File
// C++ Header - DataWindow.h - version 0.1 (2014/06/28)
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include <QDialog>
#include "WMI.h"
#include <QButtonGroup>

namespace Ui {
class DataWindow;
}

//-----------------------------------------------------------------
// DataWindow Class
//-----------------------------------------------------------------
class DataWindow : public QDialog
{
    Q_OBJECT

public:
	//---------------------------
	// Constructor(s)
	//---------------------------
    explicit DataWindow(WMI* wmi, QString lineText, QWidget *parent = 0);

	//---------------------------
	// Destructor
	//---------------------------
    ~DataWindow();

	//---------------------------
	// General Methods
	//---------------------------

	QString getLinetext();

	public slots:
	//---------------------------
	// General Slots
	//---------------------------
		void hardwareButtonClicked();
		void sensorButtonClicked();
		void selectDeselectClicked();
		void accept();
		void reject();
		void filter();

private:
	void fillCells(vector<string>, vector<string>);
	void fillComboBox();
	void clearTables();
	
	// -------------------------
	// Datamembers
	// -------------------------
    Ui::DataWindow *ui;

	WMI* wmi_;
	QString lineText_;

	// -------------------------
	// Disabling default copy constructor and default assignment operator.
	// If you get a linker error from one of these functions, your class is internally trying to use them. This is
	// an error in your class, these declarations are deliberately made without implementation because they should never be used.
	// -------------------------
	DataWindow(const DataWindow& t);
	DataWindow& operator=(const DataWindow& t);
};
