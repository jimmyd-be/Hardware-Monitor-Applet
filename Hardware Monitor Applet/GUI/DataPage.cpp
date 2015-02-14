#include "DataPage.h"


DataPage::DataPage(ScreenTypePage * type, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenTypePage_(type)
{
	setTitle(tr("Select data"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.HWiNFO_tableWidget->hideColumn(0);
	ui.OHM_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(5);

	connect(ui.Add_pushButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	connect(ui.Remove_pushButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));
}

DataPage::DataPage(ScreenTypePage * type, QList<LineText> data, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenTypePage_(type)
{
	setTitle(tr("Select data"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.HWiNFO_tableWidget->hideColumn(0);
	ui.OHM_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(5);

	connect(ui.Add_pushButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	connect(ui.Remove_pushButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));

	loadSelecteddata(data);
}

DataPage::~DataPage()
{
	if (widget_ == nullptr)
	{
		delete widget_;
		widget_ = nullptr;
	}

	if (layout_ == nullptr)
	{
		delete layout_;
		layout_ = nullptr;
	}
}

bool DataPage::validatePage()
{
	return true;
}

void DataPage::initializePage()
{
	clearData(MonitorSystem::HWiNFO);
	clearData(MonitorSystem::OHM);

	loadData(MonitorSystem::HWiNFO);
	loadData(MonitorSystem::OHM);

	if (screenTypePage_->getScreenType() == ScreenType::Graph)
	{
		ui.Precision_spinBox->setDisabled(true);
	}
}

void DataPage::loadData(MonitorSystem system)
{
	QVector<HardwareSensor> data = Data::Instance()->getAllData(system);

	QTableWidget * widget = nullptr;

	if (system == MonitorSystem::HWiNFO)
	{
		widget = ui.HWiNFO_tableWidget;
	}
	else if (system == MonitorSystem::OHM)
	{
		widget = ui.OHM_tableWidget;
	}

	for (int row = 0; row < data.size(); row++)
	{
		HardwareSensor sensor = data[row];

		widget->insertRow(row);

		QTableWidgetItem * idItem = new QTableWidgetItem();
		QTableWidgetItem * nameItem = new QTableWidgetItem();
		QTableWidgetItem * minItem = new QTableWidgetItem();
		QTableWidgetItem * maxItem = new QTableWidgetItem();
		QTableWidgetItem * currentItem = new QTableWidgetItem();

		idItem->setText(sensor.id);
		nameItem->setText(sensor.name);
		minItem->setText(QString::number(sensor.min, 'f', 2) + sensor.unit);
		maxItem->setText(QString::number(sensor.max, 'f', 2) + sensor.unit);
		currentItem->setText(QString::number(sensor.value, 'f', 2) + sensor.unit);

		widget->setItem(row, 0, idItem);
		widget->setItem(row, 1, nameItem);
		widget->setItem(row, 2, minItem);
		widget->setItem(row, 3, maxItem);
		widget->setItem(row, 4, currentItem);
	}
}

void DataPage::clearData(MonitorSystem system)
{
	QTableWidget * widget = nullptr;

	if (system == MonitorSystem::HWiNFO)
	{
		widget = ui.HWiNFO_tableWidget;
	}
	else if (system == MonitorSystem::OHM)
	{
		widget = ui.OHM_tableWidget;
	}

	widget->clearContents();
}

void DataPage::addButtonClicked()
{
	QList<QTableWidgetItem*> selectedItems;
	QTableWidget * tableWidget;
	QString system;

	int newRow = ui.SelectedItems_tableWidget->rowCount();

	if (ui.TabWidget->currentWidget() == ui.OHMTab)
	{
		selectedItems = ui.OHM_tableWidget->selectedItems();
		tableWidget = ui.OHM_tableWidget;

		system = Defines::translateMonitorSystemEnum(MonitorSystem::OHM);
	}
	else if (ui.TabWidget->currentWidget() == ui.HWiNFOTab)
	{
		selectedItems = ui.HWiNFO_tableWidget->selectedItems();
		tableWidget = ui.HWiNFO_tableWidget;

		system = Defines::translateMonitorSystemEnum(MonitorSystem::HWiNFO);
	}

	for (QTableWidgetItem * item : selectedItems)
	{
		if (!(screenTypePage_->getScreenType() == ScreenType::Graph && item->column() == 1))
		{
			Query queryItem;
			queryItem.identifier = tableWidget->item(item->row(), 0)->text();
			queryItem.name = tableWidget->item(item->row(), 1)->text();
			queryItem.system = Defines::translateMonitorSystemEnum(system);
			queryItem.value = Defines::translateQueryValueEnum(tableWidget->horizontalHeaderItem(item->column())->text());
			queryItem.precision = ui.Precision_spinBox->value();
			queryItem.addUnit = ui.unit_checkBox->isChecked();

			if (isUnique(queryItem))
			{
				ui.SelectedItems_tableWidget->insertRow(newRow);

				QTableWidgetItem * idItem = new QTableWidgetItem();
				QTableWidgetItem * nameItem = new QTableWidgetItem();
				QTableWidgetItem * systemItem = new QTableWidgetItem();
				QTableWidgetItem * valueItem = new QTableWidgetItem();
				QTableWidgetItem * precisionItem = new QTableWidgetItem();
				QTableWidgetItem * symbolItem = new QTableWidgetItem();
				QTableWidgetItem * unitItem = new QTableWidgetItem();

				idItem->setText(queryItem.identifier);
				nameItem->setText(queryItem.name);
				systemItem->setText(system);
				valueItem->setText(tableWidget->horizontalHeaderItem(item->column())->text());
				precisionItem->setText(QString::number(queryItem.precision));
				symbolItem->setText(foundNextSymbol());
				unitItem->setText(QString(ui.unit_checkBox->isChecked() ? "True" : "False"));

				ui.SelectedItems_tableWidget->setItem(newRow, 0, idItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 1, systemItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 2, nameItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 3, valueItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 4, precisionItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 5, symbolItem);
				ui.SelectedItems_tableWidget->setItem(newRow, 6, unitItem);

				newRow += 1;
			}
		}
	}
}

void DataPage::removeButtonClicked()
{
	QList<QTableWidgetItem*> items = ui.SelectedItems_tableWidget->selectedItems();

	ui.SelectedItems_tableWidget->removeRow(items[0]->row());
}

bool DataPage::isUnique(Query item)
{
	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
		QTableWidget * widget = ui.SelectedItems_tableWidget;

		if (widget->item(row, 0)->text() == item.identifier &&
			widget->item(row, 1)->text() == Defines::translateMonitorSystemEnum(item.system) &&
			widget->item(row, 2)->text() == item.name &&
			widget->item(row, 3)->text() == Defines::translateQueryValueEnum(item.value) &&
			widget->item(row, 4)->text() == QString::number(item.precision) &&
			widget->item(row, 6)->text() == QString(item.addUnit ? "True" : "False"))
		{
			return false;
		}
	}

	return true;
}

QString DataPage::foundNextSymbol()
{
	QList<QString> symbolList;

	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount()-1; row++)
	{
		QTableWidget * widget = ui.SelectedItems_tableWidget;

		symbolList.append(widget->item(row, 5)->text());
	}

	for (int i = 0; i < symbolList.size(); i++)
	{
		QString symbol = '$' + QString::number(i+1);
		if (!symbolList.contains(symbol))
		{
			return symbol;
		}
	}

	return '$' + QString::number(ui.SelectedItems_tableWidget->rowCount());
}

QMap<QString, Query> DataPage::getData()
{
	QMap<QString, Query> returnMap;

	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
		Query queryItem;

		QTableWidget * widget = ui.SelectedItems_tableWidget;

		queryItem.identifier = widget->item(row, 0)->text();
		queryItem.system = Defines::translateMonitorSystemEnum(widget->item(row, 1)->text());
		queryItem.name = widget->item(row, 2)->text();
		queryItem.value = Defines::translateQueryValueEnum(widget->item(row, 3)->text());
		queryItem.precision = widget->item(row, 4)->text().toInt();

		if (widget->item(row, 6)->text() == "True")
		{
			queryItem.addUnit = true;
		}
		else
		{
			queryItem.addUnit = false;
		}

		returnMap.insert(widget->item(row, 5)->text(), queryItem);
	}

	return returnMap;
}

int DataPage::nextId() const
{
	if (screenTypePage_->getScreenType() == ScreenType::Normal)
	{
		return Page::Page_LineEdit;
	}
	else if (screenTypePage_->getScreenType() == ScreenType::Graph)
	{
		return Page::Page_GraphEdit;
	}

	return Page::Page_LineEdit;
}

void DataPage::loadSelecteddata(QList<LineText> data)
{
	int row = 0;

	for (LineText line : data)
	{
		QMap<QString, Query>::const_iterator i = line.queryMap.constBegin();

		while (i != line.queryMap.constEnd())
		{
			ui.SelectedItems_tableWidget->insertRow(row);

			QTableWidgetItem * idItem = new QTableWidgetItem();
			QTableWidgetItem * nameItem = new QTableWidgetItem();
			QTableWidgetItem * systemItem = new QTableWidgetItem();
			QTableWidgetItem * valueItem = new QTableWidgetItem();
			QTableWidgetItem * precisionItem = new QTableWidgetItem();
			QTableWidgetItem * symbolItem = new QTableWidgetItem();
			QTableWidgetItem * unitItem = new QTableWidgetItem();

			idItem->setText(i.value().identifier);
			nameItem->setText(i.value().name);
			systemItem->setText(Defines::translateMonitorSystemEnum(i.value().system));
			valueItem->setText(Defines::translateQueryValueEnum(i.value().value));
			precisionItem->setText(QString::number(i.value().precision));
			symbolItem->setText(i.key());
			unitItem->setText(QString(i.value().addUnit ? "True" : "False"));

			ui.SelectedItems_tableWidget->setItem(row, 0, idItem);
			ui.SelectedItems_tableWidget->setItem(row, 1, systemItem);
			ui.SelectedItems_tableWidget->setItem(row, 2, nameItem);
			ui.SelectedItems_tableWidget->setItem(row, 3, valueItem);
			ui.SelectedItems_tableWidget->setItem(row, 4, precisionItem);
			ui.SelectedItems_tableWidget->setItem(row, 5, symbolItem);
			ui.SelectedItems_tableWidget->setItem(row, 6, unitItem);

			row += 1;
			++i;
		}
	}
}