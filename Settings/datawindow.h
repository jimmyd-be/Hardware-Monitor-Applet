#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include "WMI.h"

namespace Ui {
class DataWindow;
}

class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(WMI* wmi, QString lineText, QWidget *parent = 0);
    ~DataWindow();

private:

	void fillCells();
	void clearTables();

    Ui::DataWindow *ui;

	WMI* wmi_;
	QString lineText_;

};

#endif // DATAWINDOW_H
