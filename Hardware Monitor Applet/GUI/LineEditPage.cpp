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

LineEditPage::LineEditPage(DataPage* page, QList<LineText> lines, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), dataPage_(page)
{
	setTitle(tr("Insert text"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	loadLines(lines);
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

int LineEditPage::nextId() const
{
	return Page::Page_Customize;
}

void LineEditPage::loadLines(QList<LineText> lines)
{
	if (lines.size() >= 1)
	{
		ui.lineEdit1->setText(lines[0].text);
	}

	if (lines.size() >= 2)
	{
		ui.lineEdit2->setText(lines[1].text);
	}

	if (lines.size() >= 3)
	{
		ui.lineEdit3->setText(lines[2].text);
	}

	if (lines.size() >= 4)
	{
		ui.lineEdit4->setText(lines[3].text);
	}

	if (lines.size() >= 5)
	{
		ui.lineEdit5->setText(lines[4].text);
	}

	if (lines.size() >= 6)
	{
		ui.lineEdit6->setText(lines[5].text);
	}

	if (lines.size() >= 7)
	{
		ui.lineEdit7->setText(lines[6].text);
	}

	if (lines.size() >= 8)
	{
		ui.lineEdit8->setText(lines[7].text);
	}

	if (lines.size() >= 9)
	{
		ui.lineEdit9->setText(lines[8].text);
	}

	if (lines.size() >= 10)
	{
		ui.lineEdit10->setText(lines[9].text);
	}

	if (lines.size() >= 11)
	{
		ui.lineEdit11->setText(lines[10].text);
	}

	if (lines.size() >= 12)
	{
		ui.lineEdit12->setText(lines[11].text);
	}

	if (lines.size() >= 13)
	{
		ui.lineEdit13->setText(lines[12].text);
	}

	if (lines.size() >= 14)
	{
		ui.lineEdit14->setText(lines[13].text);
	}

	if (lines.size() >= 15)
	{
		ui.lineEdit15->setText(lines[14].text);
	}
}