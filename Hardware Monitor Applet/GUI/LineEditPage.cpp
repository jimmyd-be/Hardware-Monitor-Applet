#include "LineEditPage.h"


LineEditPage::LineEditPage(DataPage* page, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), dataPage_(page)
{
	setTitle(tr("Insert text"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

}

LineEditPage::~LineEditPage()
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

bool LineEditPage::validatePage()
{
	return true;
}

void LineEditPage::initializePage()
{
	int newRow = 0;

	ui.Data_tableWidget->hideColumn(0);

	QMap<QString, Query> items = dataPage_->getData();

	ui.Data_tableWidget->setRowCount(items.size());

	QMap<QString, Query>::const_iterator i = items.constBegin();
	
	while (i != items.constEnd())
	{
		QTableWidgetItem * idItem = new QTableWidgetItem();
		QTableWidgetItem * nameItem = new QTableWidgetItem();
		QTableWidgetItem * systemItem = new QTableWidgetItem();
		QTableWidgetItem * valueItem = new QTableWidgetItem();
		QTableWidgetItem * precisionItem = new QTableWidgetItem();
		QTableWidgetItem * symbolItem = new QTableWidgetItem();

		idItem->setText(i.value().identifier);
		nameItem->setText(i.value().name);
		systemItem->setText(Defines::translateMonitorSystemEnum(i.value().system));
		valueItem->setText(Defines::translateQueryValueEnum(i.value().value));
		precisionItem->setText(QString::number(i.value().precision));
		symbolItem->setText(i.key());

		ui.Data_tableWidget->setItem(newRow, 0, idItem);
		ui.Data_tableWidget->setItem(newRow, 1, symbolItem);
		ui.Data_tableWidget->setItem(newRow, 2, nameItem);
		ui.Data_tableWidget->setItem(newRow, 3, systemItem);
		ui.Data_tableWidget->setItem(newRow, 4, valueItem);
		ui.Data_tableWidget->setItem(newRow, 5, precisionItem);
		
		++i;
		newRow++;
	}
}

QStringList LineEditPage::getData()
{
	QStringList lineList;

	lineList.append(ui.lineEdit1->text());
	lineList.append(ui.lineEdit2->text());
	lineList.append(ui.lineEdit3->text());
	lineList.append(ui.lineEdit4->text());
	lineList.append(ui.lineEdit5->text());
	lineList.append(ui.lineEdit6->text());
	lineList.append(ui.lineEdit7->text());
	lineList.append(ui.lineEdit8->text());
	lineList.append(ui.lineEdit9->text());
	lineList.append(ui.lineEdit10->text());
	lineList.append(ui.lineEdit11->text());
	lineList.append(ui.lineEdit12->text());
	lineList.append(ui.lineEdit13->text());
	lineList.append(ui.lineEdit14->text());
	lineList.append(ui.lineEdit15->text());

	return lineList;
}