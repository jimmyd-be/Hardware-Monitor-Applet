#include "DataPage.h"


DataPage::DataPage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Select data"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	registerField("SelectedData", ui.SelectedItems_tableWidget);

	loadData(MonitorSystem::HWiNFO);
	loadData(MonitorSystem::OHM);
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

	for (HardwareSensor sensor : data)
	{
		int row = widget->rowCount() + 1;

		widget->insertRow(row);

		QTableWidgetItem * idItem = new QTableWidgetItem();
		QTableWidgetItem * nameItem = new QTableWidgetItem();
		QTableWidgetItem * minItem = new QTableWidgetItem();
		QTableWidgetItem * maxItem = new QTableWidgetItem();
		QTableWidgetItem * currentItem = new QTableWidgetItem();

		idItem->setText(sensor.id);
		nameItem->setText(sensor.name);
		minItem->setText(QString::number(sensor.min));
		maxItem->setText(QString::number(sensor.max));
		currentItem->setText(QString::number(sensor.value));

		widget->setItem(row, 0, idItem);
		widget->setItem(row, 1, nameItem);
		widget->setItem(row, 2, minItem);
		widget->setItem(row, 3, maxItem);
		widget->setItem(row, 4, currentItem);

	}
}