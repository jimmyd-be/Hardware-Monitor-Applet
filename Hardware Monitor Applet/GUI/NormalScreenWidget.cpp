#include "NormalScreenWidget.h"

NormalScreenWidget::NormalScreenWidget(QString name, Logitech * lcd, QWidget *parent)
	: QWidget(parent), name_(name), lcd_(lcd)
{
	setupUi(this);

	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataScreen()));
	connect(addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataDialog()));
	connect(fontButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));

	KeyboardTypes type = lcd_->getKeyboardType();

	if (type == KeyboardTypes::Monochrome)
	{
		backgroundBrowseButton->hide();
		backgroundLabel->hide();
		backgroundLine->hide();
	}
	else
	{
		backgroundBrowseButton->show();
		backgroundLabel->show();
		backgroundLine->show();
	}

	dataTableWidget->setColumnHidden(0, true);
}


NormalScreenWidget::~NormalScreenWidget()
{
	for (LineScreenWidget * widget : lineList_)
	{
		if (widget != nullptr)
		{
			delete widget;
			widget = nullptr;
		}
	}
}

void NormalScreenWidget::openDataScreen()
{
	dataDialog_ = new DataDialog(lcd_->getScreenData(name_), this);

	dataDialog_->exec();

	dataTableWidget->clearContents();
	dataMap_.clear();

	for (Query data : dataDialog_->getData())
	{
		int row = dataTableWidget->rowCount();

		dataTableWidget->insertRow(row);

		QTableWidgetItem * idItem = new QTableWidgetItem();
		QTableWidgetItem * nameItem = new QTableWidgetItem();
		QTableWidgetItem * systemItem = new QTableWidgetItem();
		QTableWidgetItem * valueItem = new QTableWidgetItem();
		QTableWidgetItem * symbolItem = new QTableWidgetItem();

		idItem->setFlags(Qt::ItemIsEnabled);
		nameItem->setFlags(Qt::ItemIsEnabled);
		systemItem->setFlags(Qt::ItemIsEnabled);
		valueItem->setFlags(Qt::ItemIsEnabled);
		symbolItem->setFlags(Qt::ItemIsEnabled);

		idItem->setText(data.identifier);
		nameItem->setText(data.name);

		switch (data.system)
		{
		case MonitorSystem::HWiNFO:
			systemItem->setText("HWiNFO");
			break;
		case MonitorSystem::OHM:
			systemItem->setText("OHM");
			break;
		};

		switch (data.value)
		{
		case QueryValue::Current:
			valueItem->setText("Current");
			break;

		case QueryValue::Max:
			valueItem->setText("Max");
			break;
		case QueryValue::Min:
			valueItem->setText("Min");
			break;
		case QueryValue::Name:
			valueItem->setText("Name");
			break;
		};

		QString querySymbol = "$" + QString::number(row + 1);
		symbolItem->setText(querySymbol);

		dataTableWidget->setItem(row, 0, idItem);
		dataTableWidget->setItem(row, 1, symbolItem);
		dataTableWidget->setItem(row, 2, nameItem);
		dataTableWidget->setItem(row, 3, systemItem);
		dataTableWidget->setItem(row, 4, valueItem);

		dataMap_.insert(querySymbol, data);
	}

	if (dataDialog_ != nullptr)
	{
		delete dataDialog_;
		dataDialog_ = nullptr;
	}
}

void NormalScreenWidget::addLine()
{
	LineScreenWidget * widget = new LineScreenWidget(this);

	linesLayout->addWidget(widget);

	lineList_.push_back(widget);
}

void NormalScreenWidget::removeWidget(LineScreenWidget * deleteWidget)
{
	linesLayout->removeWidget(deleteWidget);

	int position = lineList_.indexOf(deleteWidget);

	lineList_.remove(position);

	delete deleteWidget;
	deleteWidget = nullptr;

	lineScreenTextChanged();
}

void NormalScreenWidget::lineScreenTextChanged()
{
	lcd_->clearPage(name_);

	for (LineScreenWidget * widget : lineList_)
	{
		QMap<QString, Query> dataMap;

		QString lineText = widget->getText();

		QMapIterator<QString, Query> iter(dataMap_);

		while (iter.hasNext())
		{
			iter.next();

			if (lineText.contains(iter.key()))
			{
				dataMap.insert(iter.key(), iter.value());
			}
		}

		lcd_->addLine(name_, lineText, dataMap);
	}
}

void NormalScreenWidget::openFontDialog()
{
	FontDialog * dialog = new FontDialog(lcd_->getScreenData(name_), this);

	dialog->exec();

	AppletFont font = dialog->getFont();

	delete dialog;
}