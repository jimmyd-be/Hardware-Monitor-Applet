#include "DataPage.h"


DataPage::DataPage(ScreenTypePage * type, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenTypePage_(type)
{
	makeWindow();
}

DataPage::DataPage(ScreenTypePage * type, QList<LineText> data, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenTypePage_(type)
{
	makeWindow();
	loadSelecteddata(data);
}

DataPage::DataPage(ScreenTypePage* type, QList<GraphLine> data, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenTypePage_(type)
{
	makeWindow();
	loadSelecteddata(data);
}

DataPage::~DataPage()
{
    for(int i =0; i < ui.SelectedItems_tableWidget->rowCount(); i++)
    {
        delete ui.SelectedItems_tableWidget->cellWidget(i, 3);
    }

    for(int i =0; i < ui.SelectedItems_tableWidget->rowCount(); i++)
    {
        QWidget * fieldWidget = ui.SelectedItems_tableWidget->cellWidget(i, 8);

        if(fieldWidget != nullptr)
        {
            delete fieldWidget;
        }
    }


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

void DataPage::makeWindow()
{
	setTitle(tr("Select data"));
	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.HWiNFO_tableWidget->hideColumn(0);
	ui.OHM_tableWidget->hideColumn(0);
    ui.Influx_tableWidget->hideColumn(0);
	ui.SelectedItems_tableWidget->hideColumn(0);
    //ui.SelectedItems_tableWidget->hideColumn(5);

	ui.HWiNFO_tableWidget->horizontalHeader()->setSectionsMovable(true);
	ui.OHM_tableWidget->horizontalHeader()->setSectionsMovable(true);
    ui.Influx_tableWidget->horizontalHeader()->setSectionsMovable(true);
	ui.SelectedItems_tableWidget->horizontalHeader()->setSectionsMovable(true);

    #ifdef __linux__
    ui.TabWidget->removeTab(0);
    ui.TabWidget->removeTab(0);
    #endif

	connect(ui.Add_pushButton, SIGNAL(clicked()), this, SLOT(addButtonClicked()));
	connect(ui.Remove_pushButton, SIGNAL(clicked()), this, SLOT(removeButtonClicked()));
}

void DataPage::loadSelecteddata(QList<GraphLine> data)
{
	int row = 0;

	for (GraphLine line : data)
	{
		HardwareSensor sensor = Data::Instance()->translateLine(line.query);

        insertLineToSelectedData(row, line.query.identifier, line.query.name, Defines::translateMonitorSystemEnum(line.query.system), Defines::translateQueryValueEnum(line.query.value), QString::number(line.query.precision), "", sensor.unit, sensor.hardware, sensor.field);

		row += 1;
	}
}

bool DataPage::validatePage()
{
	return true;
}

void DataPage::initializePage()
{
#ifdef _WIN32
	clearData(MonitorSystem::HWiNFO);
	clearData(MonitorSystem::OHM);

	loadData(MonitorSystem::HWiNFO);
	loadData(MonitorSystem::OHM);
#endif
    clearData(MonitorSystem::INFLUXDB);
    loadData(MonitorSystem::INFLUXDB);
}

void DataPage::loadData(MonitorSystem system)
{
    data = Data::Instance()->getAllData(system);

	QTableWidget * widget = nullptr;
    bool addExtraField = false;

	if (system == MonitorSystem::HWiNFO)
	{
		widget = ui.HWiNFO_tableWidget;
	}
	else if (system == MonitorSystem::OHM)
	{
		widget = ui.OHM_tableWidget;
	}
    else if(system == MonitorSystem::INFLUXDB)
    {
        widget = ui.Influx_tableWidget;
        addExtraField = true;
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
		QTableWidgetItem * hardwareItem = new QTableWidgetItem();

		idItem->setText(sensor.id);
		nameItem->setText(sensor.name);
		minItem->setText(QString::number(sensor.min, 'f', 2) + sensor.unit);
		maxItem->setText(QString::number(sensor.max, 'f', 2) + sensor.unit);
		currentItem->setText(QString::number(sensor.value, 'f', 2) + sensor.unit);
		hardwareItem->setText(sensor.hardware);

		widget->setItem(row, 0, idItem);
		widget->setItem(row, 1, hardwareItem);
		widget->setItem(row, 2, nameItem);
		widget->setItem(row, 3, minItem);
		widget->setItem(row, 4, maxItem);
		widget->setItem(row, 5, currentItem);
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
    else if(system == MonitorSystem::INFLUXDB)
    {
        widget = ui.Influx_tableWidget;
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
    else if (ui.TabWidget->currentWidget() == ui.InfluxTab)
    {
        selectedItems = ui.Influx_tableWidget->selectedItems();
        tableWidget = ui.Influx_tableWidget;

        system = Defines::translateMonitorSystemEnum(MonitorSystem::INFLUXDB);
    }

	for (QTableWidgetItem * item : selectedItems)
	{
		if (!(screenTypePage_->getScreenType() == ScreenType::Graph && item->column() == 1 && item->column() == 2))
		{
			Query queryItem;
			queryItem.identifier = tableWidget->item(item->row(), 0)->text();
			queryItem.name = tableWidget->item(item->row(), 2)->text();
			queryItem.system = Defines::translateMonitorSystemEnum(system);
			queryItem.value = Defines::translateQueryValueEnum(tableWidget->horizontalHeaderItem(item->column())->text());
            queryItem.precision = 0;
            queryItem.hardware = tableWidget->item(item->row(), 1)->text();

			HardwareSensor sensor = Data::Instance()->translateLine(queryItem);

            insertLineToSelectedData(newRow, queryItem.identifier, queryItem.name, system, tableWidget->horizontalHeaderItem(item->column())->text(), QString::number(queryItem.precision), foundNextSymbol(), sensor.unit, tableWidget->item(item->row(), 1)->text(), sensor.field);

            newRow += 1;
		}
	}
}

void DataPage::removeButtonClicked()
{
	QList<QTableWidgetItem*> items = ui.SelectedItems_tableWidget->selectedItems();

	if (items.size() > 0)
	{
		ui.SelectedItems_tableWidget->removeRow(items[0]->row());
	}
}

//TODO check if this method can be deleted
bool DataPage::isUnique(Query item, HardwareSensor sensor)
{
	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
		QTableWidget * widget = ui.SelectedItems_tableWidget;

		if (widget->item(row, 0)->text() == item.identifier &&
			widget->item(row, 1)->text() == Defines::translateMonitorSystemEnum(item.system) &&
			widget->item(row, 2)->text() == item.name &&
			widget->item(row, 3)->text() == Defines::translateQueryValueEnum(item.value) &&
			widget->item(row, 4)->text() == QString::number(item.precision) &&
            widget->item(row, 6)->text() == sensor.unit &&
            widget->item(row, 7)->text() == sensor.hardware)
		{
			return false;
		}
	}

	return true;
}

QString DataPage::foundNextSymbol()
{
	QList<QString> symbolList;

	QTableWidget * widget = ui.SelectedItems_tableWidget;

	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
        symbolList.append(widget->item(row, 8)->text());
	}

	for (int i = 0; i < symbolList.size(); i++)
	{
		QString symbol = '$' + QString::number(i+10);
		if (!symbolList.contains(symbol))
		{
			return symbol;
		}
	}

	return '$' + QString::number(ui.SelectedItems_tableWidget->rowCount()+10);
}

QMap<QString, Query> DataPage::getData()
{
	QMap<QString, Query> returnMap;

	QTableWidget * widget = ui.SelectedItems_tableWidget;

	for (int row = 0; row < widget->rowCount(); row++)
	{
		Query queryItem;

		queryItem.identifier = widget->item(row, 0)->text();
		queryItem.system = Defines::translateMonitorSystemEnum(widget->item(row, 1)->text());
		queryItem.name = widget->item(row, 2)->text();
        queryItem.value = Defines::translateQueryValueEnum( ((QComboBox*) widget->cellWidget(row, 3))->currentText());
		queryItem.precision = widget->item(row, 4)->text().toInt();
        queryItem.unit = widget->item(row, 5)->text();
        queryItem.hardware = widget->item(row, 6)->text();

        if(widget->cellWidget(row, 7) != nullptr) {
            queryItem.field = ((QComboBox*) widget->cellWidget(row, 7))->currentText();
        }

        returnMap.insert(widget->item(row, 8)->text(), queryItem);
	}

	return returnMap;
}

QList<Query> DataPage::getDataList()
{
	QList<Query> list;

	for (int row = 0; row < ui.SelectedItems_tableWidget->rowCount(); row++)
	{
		Query queryItem;

		QTableWidget * widget = ui.SelectedItems_tableWidget;

		queryItem.identifier = widget->item(row, 0)->text();
		queryItem.system = Defines::translateMonitorSystemEnum(widget->item(row, 1)->text());
		queryItem.name = widget->item(row, 2)->text();
		queryItem.value = Defines::translateQueryValueEnum(widget->item(row, 3)->text());
		queryItem.precision = widget->item(row, 4)->text().toInt();
        queryItem.unit = widget->item(row, 5)->text();
        queryItem.hardware = widget->item(row, 6)->text();
        queryItem.field = widget->item(row, 7)->text();

		list.append(queryItem);
	}

	return list;
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
			HardwareSensor sensor = Data::Instance()->translateLine(i.value());

			insertLineToSelectedData(row, i.value().identifier, i.value().name, Defines::translateMonitorSystemEnum(i.value().system), Defines::translateQueryValueEnum(i.value().value),
                QString::number(i.value().precision), i.key(), sensor.unit, sensor.hardware, sensor.field);

			row += 1;
			++i;
		}
	}
}

void DataPage::insertLineToSelectedData(int row,  QString id, QString name, QString system, QString value, QString precision, QString symbol, QString unitString, QString hardware, QString field)
{
	ui.SelectedItems_tableWidget->insertRow(row);

	QTableWidgetItem * idItem = new QTableWidgetItem();
	QTableWidgetItem * nameItem = new QTableWidgetItem();
	QTableWidgetItem * systemItem = new QTableWidgetItem();
	QTableWidgetItem * valueItem = new QTableWidgetItem();
	QTableWidgetItem * precisionItem = new QTableWidgetItem();
    QTableWidgetItem * symbolItem = new QTableWidgetItem();
    QTableWidgetItem * unitStringItem = new QTableWidgetItem();
	QTableWidgetItem * hardwareItem = new QTableWidgetItem();
    QTableWidgetItem * fieldItem = new QTableWidgetItem();

	idItem->setText(id);
	nameItem->setText(name);
	systemItem->setText(system);
	valueItem->setText(value);
	precisionItem->setText(precision);
    symbolItem->setText(symbol);
    unitStringItem->setText(unitString);
	hardwareItem->setText(hardware);

    systemItem->setFlags(systemItem->flags() & ~Qt::ItemIsEditable);
    hardwareItem->setFlags(hardwareItem->flags() & ~Qt::ItemIsEditable);
    nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
    symbolItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);

	ui.SelectedItems_tableWidget->setItem(row, 0, idItem);
	ui.SelectedItems_tableWidget->setItem(row, 1, systemItem);
	ui.SelectedItems_tableWidget->setItem(row, 2, nameItem);
	ui.SelectedItems_tableWidget->setItem(row, 3, valueItem);
	ui.SelectedItems_tableWidget->setItem(row, 4, precisionItem);
    ui.SelectedItems_tableWidget->setItem(row, 5, unitStringItem);
    ui.SelectedItems_tableWidget->setItem(row, 6, hardwareItem);
    ui.SelectedItems_tableWidget->setItem(row, 7, fieldItem);
     ui.SelectedItems_tableWidget->setItem(row, 8, symbolItem);
    if(system == "InfluxDb")
    {

        if(data.isEmpty())
        {
            data = Data::Instance()->getAllData(MonitorSystem::INFLUXDB);
        }

        QVector<QString> fields;

        for(int i = 0; i < data.size(); i++)
        {
            if(data[i].name == name && fields.indexOf(data[i].hardware) == -1)
            {
                fields.append(data[i].field);
            }
        }


        QComboBox* fieldCombo = new QComboBox(this);
        for(int i = 0; i < fields.size(); i++)
        {
            fieldCombo->addItem(fields[i]);
        }

        ui.SelectedItems_tableWidget->setCellWidget(row, 7, fieldCombo);

        int indexField = fieldCombo->findText(field);
        if(field != nullptr && indexField > -1) {
            fieldCombo->setCurrentIndex(indexField);
        }
    }
     else {
        fieldItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
    }
     QComboBox *editor = new QComboBox(this);
     editor->addItem("Name");
     editor->addItem("Min");
     editor->addItem("Current");
     editor->addItem("Max");

     int index = editor->findText(value);
     if(value != nullptr && index > -1) {
         editor->setCurrentIndex(index);
     }

     ui.SelectedItems_tableWidget->setCellWidget(row, 3, editor);

}
