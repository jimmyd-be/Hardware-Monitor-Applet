#include "ScreenTypePage.h"


ScreenTypePage::ScreenTypePage(KeyboardTypes type, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Type selection"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	if (type == KeyboardTypes::Monochrome)
	{
		ui.GraphScreen_radioButton->setDisabled(true);
	}
}

ScreenTypePage::ScreenTypePage(ScreenType type, KeyboardTypes keyboard, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Type selection"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	if (type == ScreenType::Graph)
	{
		ui.GraphScreen_radioButton->setChecked(true);
	}
	else if (type == ScreenType::Normal)
	{
		ui.NormalScreen_radioButton->setChecked(true);
	}
}

ScreenTypePage::~ScreenTypePage()
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
}

ScreenType ScreenTypePage::getScreenType()
{
	if (ui.NormalScreen_radioButton->isChecked())
	{
		return ScreenType::Normal;
	}
	else if (ui.GraphScreen_radioButton->isChecked())
	{
		return ScreenType::Graph;
	}

	return ScreenType::No;
}

int ScreenTypePage::nextId() const
{
	return Page::Page_Data;
}