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

	connect(ui.AddLine_pushButton, SIGNAL(clicked()), this, SLOT(addLine()));

	addLine();
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

	removeLines();
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
		QTableWidgetItem * unitItem = new QTableWidgetItem();

		idItem->setText(i.value().identifier);
		nameItem->setText(i.value().name);
		systemItem->setText(Defines::translateMonitorSystemEnum(i.value().system));
		valueItem->setText(Defines::translateQueryValueEnum(i.value().value));
		precisionItem->setText(QString::number(i.value().precision));
		symbolItem->setText(i.key());
		unitItem->setText(QString(i.value().addUnit ? "True" : "False"));

		ui.Data_tableWidget->setItem(newRow, 0, idItem);
		ui.Data_tableWidget->setItem(newRow, 1, symbolItem);
		ui.Data_tableWidget->setItem(newRow, 2, nameItem);
		ui.Data_tableWidget->setItem(newRow, 3, systemItem);
		ui.Data_tableWidget->setItem(newRow, 4, valueItem);
		ui.Data_tableWidget->setItem(newRow, 5, precisionItem);
		ui.Data_tableWidget->setItem(newRow, 6, unitItem);
		
		++i;
		newRow++;
	}
}

QStringList LineEditPage::getData()
{
	QStringList lineList;
	
	for (LineEditPageLineWidget * widget : widgetList_)
	{
		lineList.append(widget->getText());
	}

	return lineList;
}

int LineEditPage::nextId() const
{
	return Page::Page_Customize;
}

void LineEditPage::loadLines(QList<LineText> lines)
{
	removeLines();

	for (LineText text : lines)
	{
		LineEditPageLineWidget * widget = new LineEditPageLineWidget(text.text);

		ui.data_Layout->addWidget(widget);
		widgetList_.append(widget);
	}
}

void LineEditPage::removeLines()
{
	for (LineEditPageLineWidget * widget : widgetList_)
	{
		ui.data_Layout->removeWidget(widget);
		delete widget;
	}

	widgetList_.clear();
}

void LineEditPage::addLine()
{
	LineEditPageLineWidget * widget = new LineEditPageLineWidget();

	ui.data_Layout->addWidget(widget);
	widgetList_.append(widget);
}