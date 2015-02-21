#include "GraphPage.h"

GraphPage::GraphPage(DataPage* page, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), dataPage_(page)
{
	setTitle(tr("Graph settings"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout();
	layout_->addWidget(widget_);
	setLayout(layout_);

	connect(ui.fontTitle_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(ui.colorTitle_pushButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
	connect(ui.title_checkBox, SIGNAL(stateChanged(int)), this, SLOT(titleCheckBoxChanged()));
}

GraphPage::GraphPage(DataPage* page, QList<GraphLine> lines, GraphSettings settings, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), dataPage_(page), oldLines_(lines), oldSettings_(settings)
{
	setTitle(tr("Graph settings"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout();
	layout_->addWidget(widget_);
	setLayout(layout_);

	connect(ui.fontTitle_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(ui.colorTitle_pushButton, SIGNAL(clicked()), this, SLOT(openColorDialog()));
	connect(ui.title_checkBox, SIGNAL(stateChanged(int)), this, SLOT(titleCheckBoxChanged()));
}

GraphPage::~GraphPage()
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

	for (QWidget * widget : widgetItems_)
	{
		delete widget;
	}

	widgetItems_.clear();
}

void GraphPage::openFontDialog()
{
	bool ok;
	titleFont_ = QFontDialog::getFont(&ok, titleFont_);
}

void GraphPage::openColorDialog()
{
	QColorDialog dialog;
	dialog.setCurrentColor(titleColor_);

	titleColor_ = dialog.getColor();
}

void GraphPage::titleCheckBoxChanged()
{
	if (ui.title_checkBox->isChecked())
	{
		ui.fontTitle_pushButton->setDisabled(false);
		ui.colorTitle_pushButton->setDisabled(false);
	}
	else
	{
		ui.fontTitle_pushButton->setDisabled(true);
		ui.colorTitle_pushButton->setDisabled(true);
	}
}

int GraphPage::nextId() const
{
	return -1;
}

void GraphPage::initializePage()
{
	removeData();
	fillinData();
}

void GraphPage::fillinData()
{
	QList<Query> dataList = dataPage_->getDataList();

	for (Query data : dataList)
	{
		bool found = false;
		GraphPageLineWidget * newWidget = nullptr;

		for (GraphLine line : oldLines_)
		{
			if (data == line.query)
			{
				newWidget = new GraphPageLineWidget(line);
				found = true;
			}
		}

		if (!found)
		{
			newWidget = new GraphPageLineWidget(data.name, data);
		}

		ui.Data_verticalLayout->addWidget(newWidget);

		widgetItems_.append(newWidget);
	}

	if (oldSettings_.addTitle)
	{
		ui.title_checkBox->setChecked(true);
		titleFont_ = oldSettings_.titleFont;
		titleColor_ = oldSettings_.titleColor;
		ui.Range_spinBox->setValue(oldSettings_.range);
	}
	else
	{
		ui.title_checkBox->setChecked(false);
		ui.fontTitle_pushButton->setDisabled(true);
		ui.colorTitle_pushButton->setDisabled(true);
	}
}

void GraphPage::removeData()
{
	for (QWidget * widget : widgetItems_)
	{
		ui.Data_verticalLayout->removeWidget(widget);
		delete widget;
	}

	widgetItems_.clear();
}

QMap<QString, Query> GraphPage::getValues()
{
	QMap<QString, Query> map;

	for (GraphPageLineWidget * widget : widgetItems_)
	{
		QPair<QString, Query> pair = widget->getValue();

		map.insert(pair.first, pair.second);
	}

	return map;
}

QList<QColor> GraphPage::getColors()
{
	QList<QColor> colorList;

	for (GraphPageLineWidget * widget : widgetItems_)
	{
		colorList.append(widget->getColor());
	}

	return colorList;
}


GraphSettings GraphPage::getGraphSettings()
{
	GraphSettings settings;

	settings.addTitle = ui.title_checkBox->isChecked();

	if (settings.addTitle)
	{
		settings.titleColor = titleColor_;
		settings.titleFont = titleFont_;
	}

	settings.range = ui.Range_spinBox->value();

	return settings;
}