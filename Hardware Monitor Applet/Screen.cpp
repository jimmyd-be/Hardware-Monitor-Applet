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
Screen::Screen(CEzLcd * logitech, QString name) : lcd_(logitech), background_(nullptr), name_(name)
{
	screenId_ = lcd_->AddNewPage();
}

Screen::~Screen()
{
	lcd_->RemovePage(screenId_);

	if (background_ != nullptr)
	{
		DeleteObject(background_);
		background_ = nullptr;
	}

	screenLines_.clear();
}

ScreenType Screen::getScreenType()
{
	return ScreenType::No;
}

void Screen::update()
{
	//Nothing to do
}

QString Screen::getName()
{
	return name_;
}

QList<LineText> Screen::getLines()
{
	return screenLines_;
}

void Screen::clearLines()
{
	screenLines_.clear();
}

void Screen::addLine(QString text, QMap<QString, Query> data)
{
	LineText line;

	line.text = text;
	line.queryMap = data;

	screenLines_.append(line);
}

AppletFont Screen::getFont()
{
	return font_;
}