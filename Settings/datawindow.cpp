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
	connect(ui->hardwareNames, SIGNAL(currentIndexChanged(int)), this, SLOT(filter()));
	connect(ui->sensorPushButton, SIGNAL(clicked()), this, SLOT(sensorButtonClicked()));
	connect(ui->selectDeselectButton, SIGNAL(clicked()), this, SLOT(selectDeselectClicked()));
	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	connect(ui->clocksCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->dataCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->fansCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->loadCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->temperaturesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->controlsCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->dataRateCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->levelCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->powerCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));
	connect(ui->voltagesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(filter()));

	vector<string> list;

	fillComboBox();
	fillCells(list, list);
}

DataWindow::~DataWindow()
{
	delete ui;
}

void DataWindow::fillCells(vector<string> hardwareCode = vector<string>(), vector<string> sensorType = vector<string>())
{
	clearTables();

	wmi_->refresh();

	vector<Sensor> sensor = wmi_->getSensors(hardwareCode, sensorType);

	ui->sensorTableWidget->setRowCount(sensor.size());

	for (int i = 0; i < sensor.size(); i++)
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

void DataWindow::sensorButtonClicked()
{
	QList <QTableWidgetItem  *> items = ui->sensorTableWidget->selectedItems();

	if (items.size() != 0)
	{
		int row = items[0]->row();
		int column = items[0]->column();

		QString id = ui->sensorTableWidget->verticalHeaderItem(row)->text();
		QString item = ui->sensorTableWidget->horizontalHeaderItem(column)->text();

		QString code = wmi_->generateCode("Sensor", QString::fromStdString(wmi_->getSensorIdentifier(id)), item, ui->spinBox->value());

		QString text = ui->lineEdit->text();
		text.append(code);

		ui->lineEdit->setText(text);

		wmi_->convertCodeToLine(text.toUtf8().constData());
	}
}

void DataWindow::selectDeselectClicked()
{
	if (ui->clocksCheckBox->isChecked())
	{
		ui->clocksCheckBox->setChecked(false);
		ui->dataCheckBox->setChecked(false);
		ui->fansCheckBox->setChecked(false);
		ui->loadCheckBox->setChecked(false);
		ui->temperaturesCheckBox->setChecked(false);
		ui->controlsCheckBox->setChecked(false);
		ui->dataRateCheckBox->setChecked(false);
		ui->levelCheckBox->setChecked(false);
		ui->powerCheckBox->setChecked(false);
		ui->voltagesCheckBox->setChecked(false);
	}
	else
	{
		ui->clocksCheckBox->setChecked(true);
		ui->dataCheckBox->setChecked(true);
		ui->fansCheckBox->setChecked(true);
		ui->loadCheckBox->setChecked(true);
		ui->temperaturesCheckBox->setChecked(true);
		ui->controlsCheckBox->setChecked(true);
		ui->dataRateCheckBox->setChecked(true);
		ui->levelCheckBox->setChecked(true);
		ui->powerCheckBox->setChecked(true);
		ui->voltagesCheckBox->setChecked(true);
	}
}

void DataWindow::filter()
{
	QString hardwareName = ui->hardwareNames->currentText();

	vector<string> hardwareList;

	if (hardwareName != "All")
	{
		hardwareList = wmi_->getHardwareIdentifier(hardwareName);
	}

	vector<string> checkboxList;

	if (ui->clocksCheckBox->isChecked())
	{
		checkboxList.push_back("Clock");
	}

	if (ui->dataCheckBox->isChecked())
	{
		checkboxList.push_back("Data");
	}
	if (ui->fansCheckBox->isChecked())
	{
		checkboxList.push_back("Fan");
	}
	if (ui->loadCheckBox->isChecked())
	{
		checkboxList.push_back("Load");
	}
	if (ui->temperaturesCheckBox->isChecked())
	{
		checkboxList.push_back("Temperature");
	}
	if (ui->controlsCheckBox->isChecked())
	{
		checkboxList.push_back("Control");
	}
	if (ui->dataRateCheckBox->isChecked())
	{
		checkboxList.push_back("DataRate");
	}
	if (ui->levelCheckBox->isChecked())
	{
		checkboxList.push_back("Level");
	}
	if (ui->powerCheckBox->isChecked())
	{
		checkboxList.push_back("Power");
	}
	if (ui->voltagesCheckBox->isChecked())
	{
		checkboxList.push_back("Voltage");
	}

	fillCells(hardwareList, checkboxList);
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