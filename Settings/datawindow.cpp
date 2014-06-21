#include "datawindow.h"
#include "ui_datawindow.h"

DataWindow::DataWindow(WMI * wmi, QString lineText, QWidget *parent) :
    lineText_(lineText), wmi_(wmi), QDialog(parent),
    ui(new Ui::DataWindow)
{

	this->setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    ui->setupUi(this);

	ui->lineEdit->setText(lineText_);

	connect(ui->AddHardwareButton, SIGNAL(clicked()), this, SLOT(hardwareButtonClicked()));
	connect(ui->hardwareNames, SIGNAL(currentIndexChanged(int)), this, SLOT(hardwareButtonChanged()));
	connect(ui->sensorPushButton, SIGNAL(clicked()), this, SLOT(sensorButtonClicked()));

	 connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
     connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	 vector<string> list;

	 fillComboBox();
	 fillCells(list);
}

DataWindow::~DataWindow()
{
    delete ui;
}


void DataWindow::fillCells(vector<string> hardwareCode)
{
	clearTables();

	wmi_->refresh();

	vector<Sensor> sensor = wmi_->getSensors(hardwareCode);
	
	ui->sensorTableWidget->setRowCount(sensor.size());

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

void DataWindow::fillComboBox()
{
	vector<Hardware> hardware = wmi_->getHardware();

	ui->hardwareNames->addItem(QString::fromStdString("All"));

	for (int i = 0; i < hardware.size(); i++)
	{
		ui->hardwareNames->addItem(QString::fromStdString(hardware[i].name));
	}
}

void DataWindow::clearTables()
{
	while (ui->sensorTableWidget->rowCount() > 0)
	{
		ui->sensorTableWidget->removeRow(0);
	}
}

void DataWindow::hardwareButtonClicked()
{
	vector<string> hardWareId = wmi_->getHardwareIdentifier(ui->hardwareNames->currentText());

	if (!hardWareId.empty())
	{
		QString code = wmi_->generateCode("Hardware", QString::fromStdString(hardWareId[0]), "Name", 0);

		QString text = ui->lineEdit->text();
		text.append(code);

		ui->lineEdit->setText(text);
	}
}

void DataWindow::hardwareButtonChanged()
{
	QString hardwareName = ui->hardwareNames->currentText();

	if (hardwareName == "All")
	{
		vector<string> temp;
		fillCells(temp);
	}
	else
	{
		fillCells(wmi_->getHardwareIdentifier(hardwareName));
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