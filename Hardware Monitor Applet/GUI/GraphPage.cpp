#include "GraphPage.h"

GraphPage::GraphPage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Graph settings"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout();
	layout_->addWidget(widget_);
	setLayout(layout_);
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
}

int GraphPage::nextId() const
{
	return Page::Page_Customize;
}