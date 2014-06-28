#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include "WMI.h"
#include <QButtonGroup>

namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(WMI* wmi, QString lineText, QWidget *parent = 0);
    ~DataWindow();

	QString getLinetext();

	public slots:
		void hardwareButtonClicked();
		//void hardwareButtonChanged();
		void sensorButtonClicked();
		void selectDeselectClicked();
		void accept();
		void reject();
		void filter();

private:
	void fillCells(vector<string>, vector<string>);
	void fillComboBox();
	void clearTables();
	

    Ui::DataWindow *ui;

	WMI* wmi_;
	QString lineText_;

};

#endif // DATAWINDOW_H
