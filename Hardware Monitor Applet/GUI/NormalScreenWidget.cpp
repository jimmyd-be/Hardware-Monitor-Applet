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
		lcd_->addLine(name_, widget->getText());
	}
}

void NormalScreenWidget::openFontDialog()
{
	FontDialog * dialog = new FontDialog(lcd_->getScreenData(name_), this);
}