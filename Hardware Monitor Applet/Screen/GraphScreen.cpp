//-----------------------------------------------------------------
// GraphScreen File
// C++ Source - GraphScreen.cpp - version 0.1 (2013/06/13)
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GraphScreen.h"

//-----------------------------------------------------------------
// Defines
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// GraphScreen methods
//-----------------------------------------------------------------
GraphScreen::GraphScreen(CEzLcd * logitech, QString name) : Screen(logitech, name), Xpos_(0)
{
	plot_ = new QCustomPlot();

	plot_->plotLayout()->insertRow(0);
	plot_->plotLayout()->addElement(0, 0, new QCPPlotTitle(plot_, name));
}

GraphScreen::~GraphScreen()
{
	if (plot_ != nullptr)
	{
		delete plot_;
		plot_ = nullptr;
	}
}

ScreenType GraphScreen::getScreenType()
{
	return ScreenType::Graph;
}

void GraphScreen::draw()
{
	Xpos_++;

	QList<double> listDate = data_->translateLines(graphData_);

	for (int i = 0; i < graphData_.size(); i++)
	{
		plot_->graph(i)->addData(Xpos_, listDate[i]);
	}

	lcd_->ModifyControlsOnPage(screenPage_);

	lcd_->ModifyDisplay(LG_COLOR);

	QPixmap pixmap = plot_->toPixmap(320, 240, 1);
	HBITMAP bitmap_ = QtWin::toHBITMAP(pixmap);

	HANDLE bitmapHandle = lcd_->AddBitmap(320, 240);
	lcd_->SetBitmap(bitmapHandle, bitmap_, 1);
}

void GraphScreen::update()
{

}

void GraphScreen::setBackground(QString background)
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
		plot_->setBackground(backgroundPixMap);
	}
}

void GraphScreen::setData(QList<GraphLine> data)
{
	graphData_ = data;

	createPlot();
}

QList<GraphLine> GraphScreen::getData()
{
	return graphData_;
}

void GraphScreen::createPlot()
{
	for (int i = 0; i < graphData_.size(); i++)
	{
		plot_->addGraph();
		plot_->graph(i)->setPen(QPen(graphData_[i].color));
		plot_->graph(i)->setName(graphData_[i].text);
	}

}