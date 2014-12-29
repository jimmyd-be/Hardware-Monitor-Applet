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
}

bool CustomizePage::validatePage()
{
	return true;
}

void CustomizePage::initializePage()
{
	QStringList list = linePage_->getData();

	ui.lineEdit1->setText(list[0]);
	ui.lineEdit2->setText(list[1]);
	ui.lineEdit3->setText(list[2]);
	ui.lineEdit4->setText(list[3]);
	ui.lineEdit5->setText(list[4]);
	ui.lineEdit6->setText(list[5]);
	ui.lineEdit7->setText(list[6]);
	ui.lineEdit8->setText(list[7]);
	ui.lineEdit9->setText(list[8]);
	ui.lineEdit10->setText(list[9]);
	ui.lineEdit11->setText(list[10]);
	ui.lineEdit12->setText(list[11]);
	ui.lineEdit13->setText(list[12]);
	ui.lineEdit14->setText(list[13]);
	ui.lineEdit15->setText(list[14]);
}