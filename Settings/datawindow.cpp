#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(WMI * wmi, QString lineText, QWidget *parent) :
    lineText_(lineText), wmi_(wmi), QDialog(parent),
    ui(new Ui::DataWindow)
{
	this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);

	ui->lineEdit->setText(lineText_);

	ui->hardWareTableWidget->hideColumn(0);
	ui->sensorTableWidget->hideColumn(0);

	fillCells();
}

DataWindow::~DataWindow()
{
    delete ui;
}


void DataWindow::fillCells()
{
	wmi_->refresh();

	vector<Hardware> hardware = wmi_->getHardware();
	vector<Sensor> sensor = wmi_->getSensors();
	
	ui->hardWareTableWidget->setRowCount(hardware.size());
	ui->sensorTableWidget->setRowCount(sensor.size());

	for(int i =0; i < hardware.size(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(hardware[i].InstanceId));
		QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(hardware[i].name));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(hardware[i].hardwaretype));

		ui->hardWareTableWidget->setItem(i, 0, item);
		ui->hardWareTableWidget->setItem(i, 1, item1);
		ui->hardWareTableWidget->setItem(i, 2, item2);
	}


	for(int i =0; i < sensor.size(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(sensor[i].instanceId));
		QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(sensor[i].name));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(sensor[i].sensorType));

		QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(sensor[i].max));
		QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(sensor[i].min));
		QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(sensor[i].value));

		ui->sensorTableWidget->setItem(i, 0, item);
		ui->sensorTableWidget->setItem(i, 1, item1);
		ui->sensorTableWidget->setItem(i, 2, item2);
		ui->sensorTableWidget->setItem(i, 3, item3);
		ui->sensorTableWidget->setItem(i, 4, item4);
		ui->sensorTableWidget->setItem(i, 5, item5);
	}
}


void DataWindow::clearTables()
{
	while (ui->hardWareTableWidget->rowCount() > 0)
	{
		ui->hardWareTableWidget->removeRow(0);
	}

	while (ui->sensorTableWidget->rowCount() > 0)
	{
		ui->sensorTableWidget->removeRow(0);
	}
}