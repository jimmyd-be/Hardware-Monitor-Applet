#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(WMI * wmi, QString lineText, QWidget *parent) :
    lineText_(lineText), wmi_(wmi), QDialog(parent),
    ui(new Ui::DataWindow)
{

	this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);

	ui->lineEdit->setText(lineText_);

	connect(ui->hardwarePushButton, SIGNAL(clicked()), this, SLOT(hardwareButtonClicked()));
	connect(ui->sensorPushButton, SIGNAL(clicked()), this, SLOT(sensorButtonClicked()));

	 connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

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

		ui->hardWareTableWidget->setVerticalHeaderItem(i, item);
		ui->hardWareTableWidget->setItem(i, 0, item1);
		ui->hardWareTableWidget->setItem(i, 1, item2);
	}

	for(int i =0; i < sensor.size(); i++)
	{
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(sensor[i].instanceId));
		QTableWidgetItem* item1 = new QTableWidgetItem(QString::fromStdString(sensor[i].name));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(sensor[i].sensorType));

		QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(sensor[i].max));
		QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(sensor[i].min));
		QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(sensor[i].value));

		ui->sensorTableWidget->setVerticalHeaderItem(i, item);
		ui->sensorTableWidget->setItem(i, 0, item1);
		ui->sensorTableWidget->setItem(i, 1, item2);
		ui->sensorTableWidget->setItem(i, 2, item3);
		ui->sensorTableWidget->setItem(i, 3, item4);
		ui->sensorTableWidget->setItem(i, 4, item5);
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

void DataWindow::hardwareButtonClicked()
{
	QList <QTableWidgetItem  *> items = ui->hardWareTableWidget->selectedItems();

	if(items.size() != 0)
	{
		int row = items[0]->row();
		int column = items[0]->column();

		QString id = ui->hardWareTableWidget->verticalHeaderItem(row)->text();
		QString item = ui->hardWareTableWidget->horizontalHeaderItem(column)->text();

		QString code = wmi_->generateCode("Hardware", id, item, 0);

		QString text = ui->lineEdit->text();
		text.append(code);

		ui->lineEdit->setText(text);
	}
}

void DataWindow::sensorButtonClicked()
{
	QList <QTableWidgetItem  *> items = ui->sensorTableWidget->selectedItems();

	if(items.size() != 0)
	{
		int row = items[0]->row();
		int column = items[0]->column();

		QString id = ui->sensorTableWidget->verticalHeaderItem(row)->text();
		QString item = ui->sensorTableWidget->horizontalHeaderItem(column)->text();

		QString code = wmi_->generateCode("Sensor", id, item, ui->spinBox->value());

		QString text = ui->lineEdit->text();
		text.append(code);

		ui->lineEdit->setText(text);

		wmi_->convertCodeToLine(text.toUtf8().constData());
	}
}

void DataWindow::accept()
{
	lineText_ = ui->lineEdit->text();
	QDialog::accept();
}

void DataWindow::reject()
{
	lineText_ = "";
	QDialog::reject();
}

QString DataWindow::getLinetext()
{
	return lineText_;
}