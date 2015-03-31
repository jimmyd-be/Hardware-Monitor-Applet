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
GraphScreen::GraphScreen(CEzLcd * logitech, QString name) : Screen(logitech, name), Xpos_(0), bitmapHandle_(nullptr), bitmap_(nullptr), legendScreen_(nullptr), legendOpen_(false), settings_({0})
{
	legendScreen_ = new LegendScreen(logitech, "Legend " + name);

	plot_ = new QCustomPlot();
}

GraphScreen::~GraphScreen()
{
	if (plot_ != nullptr)
	{
		delete plot_;
		plot_ = nullptr;
	}

	if (bitmap_ != nullptr)
	{
		DeleteObject(bitmap_);
		bitmap_ = nullptr;
	}

	if (bitmapHandle_ != nullptr)
	{
		DeleteObject(bitmapHandle_);
		bitmapHandle_ = nullptr;
	}

	if (legendScreen_ != nullptr)
	{
		delete legendScreen_;
		legendScreen_ = nullptr;
	}
}

ScreenType GraphScreen::getScreenType()
{
	return ScreenType::Graph;
}

void GraphScreen::draw()
{
	if (legendOpen_)
	{
		legendScreen_->draw();
	}
	else
	{
		lcd_->ModifyControlsOnPage(screenPage_);
		lcd_->ModifyDisplay(LG_COLOR);

		if (Xpos_ >= settings_.range)
		{
			plot_->xAxis->setRange(Xpos_ - settings_.range, Xpos_);
		}
		else
		{
			plot_->xAxis->setRange(0, settings_.range);
		}

		if (settings_.yMaxRange == -1 && settings_.yMinRange == -1)
		{
			plot_->yAxis->rescale();
		}
		
		plot_->replot();

		QPixmap pixmap = plot_->toPixmap(320, 240, 1);

		if (bitmap_ != nullptr)
		{
			DeleteObject(bitmap_);
			bitmap_ = nullptr;
		}

		bitmap_ = QtWin::toHBITMAP(pixmap);

		if (bitmapHandle_ == nullptr)
		{
			bitmapHandle_ = lcd_->AddBitmap(320, 240);
		}
		lcd_->SetBitmap(bitmapHandle_, bitmap_, 1);

		lcd_->ShowPage(screenPage_);
	}
}

void GraphScreen::update()
{
	QList<double> listDate = data_->translateLines(graphData_);

	for (int i = 0; i < listDate.size(); i++)
	{
		plot_->graph(i)->addData(Xpos_, listDate[i]);
	}

	Xpos_++;
}

void GraphScreen::cleanData()
{
	if (!legendOpen_)
	{
		Xpos_ = 0;

		for (int i = 0; i < graphData_.size(); i++)
		{
			plot_->graph(i)->clearData();
		}
	}
}

GraphSettings GraphScreen::getGraphSettings()
{
	return settings_;
}

void GraphScreen::setSettings(GraphSettings settings)
{
	settings_ = settings;

	legendScreen_->setSettings(settings_);

	if (settings_.addTitle)
	{
		plot_->plotLayout()->insertRow(0);
		
		QCPPlotTitle * plotTitle = new QCPPlotTitle(plot_, name_);
		plotTitle->setFont(settings.titleFont);
		plotTitle->setTextColor(settings.titleColor);

		plot_->plotLayout()->addElement(0, 0, plotTitle);
	}

	if (settings_.yMaxRange != -1 && settings_.yMinRange != -1)
	{
		plot_->yAxis->setRange(settings_.yMinRange, settings_.yMaxRange);
	}
}

void GraphScreen::setBackground(QString background)
{
	legendScreen_->setBackground(background);

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

	legendScreen_->setData(data);

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
		plot_->graph(i)->setPen(QPen(graphData_[i].color, 2));
		plot_->graph(i)->setName(graphData_[i].text);
	}
}

void GraphScreen::openCustomScreen()
{
	legendOpen_ = !legendOpen_;
}