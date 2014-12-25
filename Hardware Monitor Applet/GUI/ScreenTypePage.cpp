#include "ScreenTypePage.h"


ScreenTypePage::ScreenTypePage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Type selection"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	registerField("ScreenType_NormalScreen", ui.NormalScreen_radioButton);
	registerField("ScreenType_GraphScreen", ui.GraphScreen_radioButton);
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
