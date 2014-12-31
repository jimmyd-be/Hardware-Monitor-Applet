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
}

GraphPage::GraphPage(DataPage* page, QList<LineText> lines, QList<QColor> colors, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), dataPage_(page)
{
	setTitle(tr("Graph settings"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout();
	layout_->addWidget(widget_);
	setLayout(layout_);

	loadData(lines, colors);
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
	QMap<QString, Query> data = dataPage_->getData();

	QMap<QString, Query>::const_iterator i = data.constBegin();

	while (i != data.constEnd())
	{
		GraphPageLineWidget * newWidget = new GraphPageLineWidget(i.key(), i.value());
		
		ui.Data_verticalLayout->addWidget(newWidget);

		widgetItems_.append(newWidget);

		++i;
	}
}

void GraphPage::loadData(QList<LineText> lines, QList<QColor> colors)
{
	removeData();

	for (int i = 0; i < lines.size(); i++)
	{
		GraphPageLineWidget * newWidget = new GraphPageLineWidget(lines[i].text, lines[i].queryMap[0]);

		ui.Data_verticalLayout->addWidget(newWidget);

		widgetItems_.append(newWidget);
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