#include "IntroPage.h"


IntroPage::IntroPage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Introduction"));

	widget_ = new QWidget();

	ui.setupUi(widget_);


	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	registerField("ScreenName", ui.ScreenName_lineEdit);
}

IntroPage::~IntroPage()
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

bool IntroPage::validatePage()
{
	if (ui.ScreenName_lineEdit->text().isEmpty())
	{
		ui.Error_label->setText("You must fillin a screenname!!");

		return false;
	}

	//Check for unique name

	return true;
}