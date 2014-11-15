#include "DataDialog.h"


DataDialog::DataDialog(QMap<QString, Query> screenData, QWidget *parent)
	: QDialog(parent)
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
	ui.selectedSensorTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Symbol"));

	ui.selectedSensorTable->setColumnHidden(0, true);

	fillinData();
	fillinSelectedData(screenData);
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

		newQuery.system = Defines::translateMonitorSystemEnum(systemString);

		QString valueString = ui.selectedSensorTable->item(row, 2)->text();

		newQuery.value = Defines::translateQueryValueEnum(valueString);

		newQuery.name = ui.selectedSensorTable->item(row, 1)->text();
		
		data_.insert(ui.selectedSensorTable->item(row, 4)->text(), newQuery);
	}

	hide();
}

void DataDialog::fillinSelectedData(QMap<QString, Query> data)
{
	ui.selectedSensorTable->clearContents();

	QMapIterator<QString, Query> iter(data);

	while (iter.hasNext())
	{
		iter.next();
		
		int row = ui.selectedSensorTable->rowCount();
		Query query = iter.value();

		ui.selectedSensorTable->insertRow(row);

		QTableWidgetItem * selectedItem = new QTableWidgetItem();
		QTableWidgetItem * selectedName = new QTableWidgetItem();
		QTableWidgetItem * selectedColumn = new QTableWidgetItem();
		QTableWidgetItem * selectedSystem = new QTableWidgetItem();
		QTableWidgetItem * symbol = new QTableWidgetItem();

		selectedItem->setText(query.identifier);
		selectedName->setText(query.name);

		selectedColumn->setText(Defines::translateQueryValueEnum(query.value));
		selectedSystem->setText(Defines::translateMonitorSystemEnum(query.system));

		symbol->setText(iter.key());

		ui.selectedSensorTable->setItem(row, 0, selectedItem);
		ui.selectedSensorTable->setItem(row, 1, selectedName);
		ui.selectedSensorTable->setItem(row, 2, selectedColumn);
		ui.selectedSensorTable->setItem(row, 3, selectedSystem);
		ui.selectedSensorTable->setItem(row, 4, symbol);
	}
}

void DataDialog::addSensor()
{
	QList<QTableWidgetItem*> items = ui.sensorTable->selectedItems();

	for (QTableWidgetItem * tableItem : items)
	{
		if (!containsItems(ui.sensorTable->item(tableItem->row(), 0)->text(), ui.sensorTable->horizontalHeaderItem(tableItem->column())->text(), getSelectedSystemString()))
		{
			int row = ui.selectedSensorTable->rowCount();

			ui.selectedSensorTable->insertRow(row);

			QTableWidgetItem * selectedItem = new QTableWidgetItem();
			QTableWidgetItem * selectedName = new QTableWidgetItem();
			QTableWidgetItem * selectedColumn = new QTableWidgetItem();
			QTableWidgetItem * selectedSystem = new QTableWidgetItem();
			QTableWidgetItem * symbol = new QTableWidgetItem();

			symbol->setText(findSymbol());

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
			ui.selectedSensorTable->setItem(row, 4, symbol);
		}
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

bool DataDialog::containsItems(QString identifier, QString value, QString system)
{
	for (int row = 0; row < ui.selectedSensorTable->rowCount(); row++)
	{
		if (ui.selectedSensorTable->item(row, 0)->text() == identifier && ui.selectedSensorTable->item(row, 2)->text() == value && ui.selectedSensorTable->item(row, 3)->text() == system)
		{
			return true;
		}
	}

	return false;
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

QMap<QString, Query> DataDialog::getData()
{
	return data_;
}

QString DataDialog::findSymbol()
{
	QVector<QString> symbols;
	int count = 1;
	bool found = false;
	QString returnSymbol;

	for (int row = 0; row < ui.selectedSensorTable->rowCount()-1; row++)
	{
		symbols.push_back(ui.selectedSensorTable->item(row, 4)->text());
	}

	while (!found)
	{
		QString symbol = "$" + QString::number(count);

		if (!symbols.contains(symbol))
		{
			returnSymbol = symbol;
			found = true;
		}

		count++;
	}

	return returnSymbol;
}