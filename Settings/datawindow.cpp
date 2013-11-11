#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(WMI * wmi, QString lineText, QWidget *parent) :
    lineText_(lineText), wmi_(wmi), QDialog(parent),
    ui(new Ui::DataWindow)
{
	this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);

	ui->lineEdit->setText(lineText_);

	//ui->hardWareTableWidget->hideColumn(0);
	//ui->sensorTableWidget->hideColumn(0);

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

QString DataWindow::generateCode(QString type, QString id, QString name, int round)
{
	QString code = "${";

	if(type == "Hardware")
	{
		code.append("H, ");
	}
	else if(type == "Sensor")
	{
		code.append("S, ");
	}

	code.append(id);
	code.append(", ");

	code.append(name);
	
	if(round != 0)
	{
		code.append(", ");
		code.append(QString::number(round));
	}

	code.append("}");

	return code;
}

void DataWindow::hardwareButtonClicked()
{
	QList <QTableWidgetItem  *> items = ui->hardWareTableWidget->selectedItems();

	if(items.size() != 0)
	{
		int row = items[0]->row();
		int column = items[0]->column();

		QString id = ui->hardWareTableWidget->itemAt(0, row)->text();
		QString item = ui->hardWareTableWidget->horizontalHeaderItem(column)->text();

		QString code = generateCode("Hardware", id, item, 0);

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

		QString id = ui->sensorTableWidget->itemAt(0, row)->text();
		QString item = ui->sensorTableWidget->horizontalHeaderItem(column)->text();

		QString code = generateCode("Sensor", id, item, ui->spinBox->value());

		QString text = ui->lineEdit->text();
		text.append(code);

		ui->lineEdit->setText(text);
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