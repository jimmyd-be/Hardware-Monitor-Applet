//-----------------------------------------------------------------
// Screen File
// C++ Source - Screen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Screen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Screen methods
//-----------------------------------------------------------------
Screen::Screen(CEzLcd * logitech, QString name) : lcd_(logitech), background_(nullptr), name_(name), backgroundString_(""), firstStart_(true)
{
	data_ = Data::Instance();

	screenPage_ = lcd_->AddNewPage();
}

Screen::~Screen()
{
	lcd_->RemovePage(screenPage_);

	if (background_ != nullptr)
	{
		DeleteObject(background_);
		background_ = nullptr;
	}
}

ScreenType Screen::getScreenType()
{
	return ScreenType::No;
}

void Screen::update()
{
	//Nothing to do
}

void Screen::draw()
{
	//Nothing to do
}

QString Screen::getName()
{
	return name_;
}

QList<QColor> Screen::getGraphColors()
{
	return graphColors_;
}

void Screen::setColors(QList<QColor> colors)
{
	graphColors_ = colors;
}

void Screen::setBackground(QString background)
{
	QString backgroundTemp = "";

	if (background.isEmpty())
	{
		backgroundTemp = ":/MainWindow/Resources/Default.png";
	}
	else
	{
		backgroundString_ = background;
		backgroundTemp = Defines::getSettingsFolder() + "/Background/" + background;
	}

	QPixmap backgroundPixMap(backgroundTemp);

	if (!backgroundPixMap.isNull())
	{
		background_ = QtWin::toHBITMAP(backgroundPixMap);

		lcd_->SetBackground(background_);
	}
}

QString Screen::getBackground()
{
	return backgroundString_;
}

CEzLcdPage* Screen::getPage()
{
	return screenPage_;
}