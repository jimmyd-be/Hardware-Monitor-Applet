#include "CustomizePage.h"


CustomizePage::CustomizePage(LineEditPage * page, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), linePage_(page)
{
	setTitle(tr("Introduction"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);
}

CustomizePage::~CustomizePage()
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

	for (QWidget * widget : widgetList_)
	{
		ui.verticalLayout->removeWidget(widget);
	}

	widgetList_.clear();
}

bool CustomizePage::validatePage()
{
	return true;
}

void CustomizePage::initializePage()
{
	for (QWidget * widget : widgetList_)
	{
		ui.verticalLayout->removeWidget(widget);
	}

	widgetList_.clear();

	QStringList list = optimizeLines(linePage_->getData());

	for (QString text : list)
	{
		CustomizePageLineWidget * widget = new CustomizePageLineWidget(text);

		ui.verticalLayout->addWidget(widget);

		widgetList_.append(widget);
	}

}

QStringList CustomizePage::optimizeLines(QStringList lineList)
{
	while (!lineList.isEmpty() && lineList.last().isEmpty())
	{
		lineList.removeLast();
	}

	return lineList;
}

int CustomizePage::nextId() const
{
	return -1;
}

QList<CustomSettings> CustomizePage::getData()
{
	QList<CustomSettings> data;


	return data;
}