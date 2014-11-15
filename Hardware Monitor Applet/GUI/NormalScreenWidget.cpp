#include "NormalScreenWidget.h"

NormalScreenWidget::NormalScreenWidget(QString name, Logitech * lcd, QWidget *parent)
	: QWidget(parent), name_(name), lcd_(lcd)
{
	setupUi(this);

	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataScreen()));
	connect(addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataDialog()));
	connect(fontButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(backgroundBrowseButton, SIGNAL(clicked()), this, SLOT(openbackgroundDialog()));

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

NormalScreenWidget::NormalScreenWidget(Screen * screen, Logitech * lcd, QWidget *parent)
	: QWidget(parent), name_(screen->getName()), lcd_(lcd)
{
	setupUi(this);

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

	fillinData(screen);

	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataScreen()));
	connect(addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
	connect(addDataButton, SIGNAL(clicked()), this, SLOT(openDataDialog()));
	connect(fontButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(backgroundBrowseButton, SIGNAL(clicked()), this, SLOT(openbackgroundDialog()));
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

void NormalScreenWidget::fillinData(Screen * screen)
{
	fontLine->setText(screen->getFont().name.toString());
	backgroundLine->setText(screen->getBackground());

	QMap<QString, Query> mapData;

	for (LineText line : screen->getLines())
	{
		addLine(line.text);

		QMapIterator<QString, Query> iter(line.queryMap);

		while (iter.hasNext())
		{
			iter.next();
			if (!mapData.contains(iter.key()))
			{
				QString test = iter.key();
				mapData.insert(iter.key(), iter.value());
			}
		}
	}
	
	QMapIterator<QString, Query> iter(mapData);

	while (iter.hasNext())
	{
		iter.next();
		addDataMap(iter.value(), iter.key());
	}
}

void NormalScreenWidget::openDataScreen()
{
	dataDialog_ = new DataDialog(dataMap_, this);

	dataDialog_->exec();

	dataTableWidget->clearContents();

	while (dataTableWidget->rowCount() != 0)
	{
		dataTableWidget->removeRow(0);
	}

	dataMap_.clear();

	QMapIterator<QString, Query> iter(dataDialog_->getData());

	while (iter.hasNext())
	{
		iter.next();
		addDataMap(iter.value(), iter.key());
	}

	if (dataDialog_ != nullptr)
	{
		delete dataDialog_;
		dataDialog_ = nullptr;
	}
}

void NormalScreenWidget::addDataMap(Query data)
{
	int row = dataTableWidget->rowCount();

	QString querySymbol = "$" + QString::number(row + 1);
	
	addDataMap(data, querySymbol);	
}

void NormalScreenWidget::addDataMap(Query data, QString querySymbol)
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

	systemItem->setText(Defines::translateMonitorSystemEnum(data.system));

	valueItem->setText(Defines::translateQueryValueEnum(data.value));

	symbolItem->setText(querySymbol);

	dataTableWidget->setItem(row, 0, idItem);
	dataTableWidget->setItem(row, 1, symbolItem);
	dataTableWidget->setItem(row, 2, nameItem);
	dataTableWidget->setItem(row, 3, systemItem);
	dataTableWidget->setItem(row, 4, valueItem);

	dataMap_.insert(querySymbol, data);
}

void NormalScreenWidget::addLine()
{
	LineScreenWidget * widget = new LineScreenWidget(this);

	linesLayout->addWidget(widget);

	lineList_.push_back(widget);
}

void NormalScreenWidget::addLine(QString text)
{
	LineScreenWidget * widget = new LineScreenWidget(text, this);

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

	lcd_->addFont(name_, font);

	delete dialog;

	fontLine->setText(font.name.toString());
}

void NormalScreenWidget::openbackgroundDialog()
{
	QFileDialog dialog;

	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Image Files (*.jpg, *.png)"));

	if (dialog.exec() != 0)
	{
		QString file = dialog.selectedFiles().at(0);

		lcd_->addBackground(name_, file);

		//backgroundLine->setText();
	}
}