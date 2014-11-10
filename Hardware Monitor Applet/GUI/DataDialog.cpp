#include "DataDialog.h"


DataDialog::DataDialog(Screen * screenData, QWidget *parent)
	: QDialog(parent), screenData_(screenData)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.MonitorSystemButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonChanged(int)));
	connect(ui.addButton, SIGNAL(clicked()), this, SLOT(addSensor()));
	connect(ui.removeButton, SIGNAL(clicked()), this, SLOT(removeSensor()));
	connect(ui.clearTableButton, SIGNAL(clicked()), this, SLOT(clearSelectionTable()));
	
	setWindowFlags(Qt::Window);

	ui.selectedSensorTable->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
	ui.selectedSensorTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
	ui.selectedSensorTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Type"));
	ui.selectedSensorTable->setHorizontalHeaderItem(3, new QTableWidgetItem("System"));

	ui.selectedSensorTable->setColumnHidden(0, true);
	

	fillinData();
}


DataDialog::~DataDialog()
{
	
}

void DataDialog::accept()
{
	data_.clear();

	for (int row = 0; row < ui.selectedSensorTable->rowCount(); row++)
	{
		Query newQuery;

		newQuery.identifier = ui.selectedSensorTable->item(row, 0)->text();

		QString systemString = ui.selectedSensorTable->item(row, 3)->text();

		if (systemString == "OHM")
		{
			newQuery.system = MonitorSystem::OHM;
		}
		else if (systemString == "HWiNFO")
		{
			newQuery.system = MonitorSystem::HWiNFO;
		}
		else
		{
			newQuery.system = MonitorSystem::NONE;
		}

		QString valueString = ui.selectedSensorTable->item(row, 2)->text();

		if (valueString == "Max")
		{
			newQuery.value = QueryValue::Max;
		}
		else if (valueString == "Min")
		{
			newQuery.value = QueryValue::Min;
		}
		else if (valueString == "Value")
		{
			newQuery.value = QueryValue::Current;
		}
		else if (valueString == "Name")
		{
			newQuery.value = QueryValue::Name;
		}

		newQuery.name = ui.selectedSensorTable->item(row, 1)->text();
		
		data_.push_back(newQuery);
	}

	hide();
}

void DataDialog::addSensor()
{
	QList<QTableWidgetItem*> items = ui.sensorTable->selectedItems();

	for (QTableWidgetItem * tableItem : items)
	{
		int row = ui.selectedSensorTable->rowCount();

		ui.selectedSensorTable->insertRow(row);

		QTableWidgetItem * selectedItem = new QTableWidgetItem();
		QTableWidgetItem * selectedName = new QTableWidgetItem();
		QTableWidgetItem * selectedColumn = new QTableWidgetItem();
		QTableWidgetItem * selectedSystem = new QTableWidgetItem();

		selectedItem->setText(ui.sensorTable->item(tableItem->row(), 0)->text());
		selectedName->setText(ui.sensorTable->item(tableItem->row(), 1)->text());
		selectedColumn->setText(ui.sensorTable->horizontalHeaderItem(tableItem->column())->text());
		selectedSystem->setText(getSelectedSystemString());

		selectedColumn->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		selectedSystem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		selectedItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		ui.selectedSensorTable->setItem(row, 0, selectedItem);
		ui.selectedSensorTable->setItem(row, 1, selectedName);
		ui.selectedSensorTable->setItem(row, 2, selectedColumn);
		ui.selectedSensorTable->setItem(row, 3, selectedSystem);
	}
}

void DataDialog::removeSensor()
{
	QList<QTableWidgetItem*> items = ui.selectedSensorTable->selectedItems();

	ui.selectedSensorTable->removeRow(items[0]->row());
}

void DataDialog::reject()
{
	ui.sensorTable->clear();
	ui.selectedSensorTable->clear();

	close();
}

void DataDialog::closeEvent(QCloseEvent * event)
{
	reject();
}

void DataDialog::radioButtonChanged(int button)
{
	fillinData();
}

void DataDialog::clearSelectionTable()
{
	ui.selectedSensorTable->clearContents();

	while (ui.selectedSensorTable->rowCount() > 0)
	{
		ui.selectedSensorTable->removeRow(0);
	}
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
	ui.sensorTable->clearContents();

	while (ui.sensorTable->rowCount() > 0)
	{
		ui.sensorTable->removeRow(0);
	}

	addHeaders();

	QVector<HardwareSensor> sensors = Data::Instance()->getAllSensors(getSelectedSystem());

	for (HardwareSensor hardwareSensors : sensors)
	{
		int row = ui.sensorTable->rowCount();

		ui.sensorTable->insertRow(row);

		QTableWidgetItem * itemId = new QTableWidgetItem(QString::fromStdString(hardwareSensors.id));
		QTableWidgetItem * itemValue = new QTableWidgetItem(QString::number(hardwareSensors.value));
		QTableWidgetItem * itemMin = new QTableWidgetItem(QString::number(hardwareSensors.min));
		QTableWidgetItem * itemMax = new QTableWidgetItem(QString::number(hardwareSensors.max));

		itemId->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		itemValue->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		itemMin->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		itemMax->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		ui.sensorTable->setItem(row, 0, itemId);
		ui.sensorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(hardwareSensors.name)));
		ui.sensorTable->setItem(row, 2, itemValue);
		ui.sensorTable->setItem(row, 3, itemMax);
		ui.sensorTable->setItem(row, 4, itemMin);
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

QString DataDialog::getSelectedSystemString()
{
	switch (getSelectedSystem())
	{
		case MonitorSystem::HWiNFO:
			return QString("HWiNFO");
		break;
		
		case MonitorSystem::OHM:
			return QString("OHM");
		break;
	};
	return "";
}

QVector<Query> DataDialog::getData()
{
	return data_;
}