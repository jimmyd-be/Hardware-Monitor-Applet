#include "DataDialog.h"


DataDialog::DataDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.MonitorSystemButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonChanged(int)));

	setWindowFlags(Qt::Window);

	fillinData();
}


DataDialog::~DataDialog()
{
}

void DataDialog::accept()
{
	
}

void DataDialog::reject()
{

}

void DataDialog::closeEvent(QCloseEvent * event)
{

}

void DataDialog::radioButtonChanged(int)
{

}

void DataDialog::addHeaders()
{
	ui.sensorTable->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
	ui.sensorTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
	ui.sensorTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Value"));
	ui.sensorTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Max"));
	ui.sensorTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Min"));

	ui.sensorTable->setColumnHidden(0, true);
}

void DataDialog::fillinData()
{
	ui.sensorTable->clear();

	addHeaders();

	QVector<HardwareSensor> sensors = Data::Instance()->getAllSensors(getSelectedSystem());

	for (HardwareSensor hardwareSensors : sensors)
	{
		int row = ui.sensorTable->rowCount();

		ui.sensorTable->insertRow(row);

		ui.sensorTable->setItem(row - 1, 0, new QTableWidgetItem(QString::fromStdString(hardwareSensors.id)));
		ui.sensorTable->setItem(row - 1, 1, new QTableWidgetItem(QString::fromStdString(hardwareSensors.name)));
		ui.sensorTable->setItem(row - 1, 2, new QTableWidgetItem(QString::number(hardwareSensors.value)));
		ui.sensorTable->setItem(row - 1, 3, new QTableWidgetItem(QString::number(hardwareSensors.max)));
		ui.sensorTable->setItem(row - 1, 4, new QTableWidgetItem(QString::number(hardwareSensors.min)));
	}
}

MonitorSystem DataDialog::getSelectedSystem()
{
	if (ui.OHMRadioButton->isChecked())
	{
		return MonitorSystem::OHM;
	}
	else if (ui.HWiNfoRadioButton->isChecked())
	{
		return MonitorSystem::HWiNFO;
	}

	return MonitorSystem::NONE;
}