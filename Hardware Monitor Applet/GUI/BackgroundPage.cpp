#include "BackgroundPage.h"


BackgroundPage::BackgroundPage(QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr)
{
	setTitle(tr("Background selection"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.Background_lineEdit->setDisabled(true);
	ui.Browse_pushButton->setDisabled(true);

	connect(ui.buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(radioButtonClicked()));
	connect(ui.Browse_pushButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
}

BackgroundPage::~BackgroundPage()
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

bool BackgroundPage::validatePage()
{
	if (ui.buttonGroup->checkedButton()->text() == "Custom background")
	{
		QImage backgroundImage;
		
		if (!backgroundImage.load(ui.Background_lineEdit->text()) || backgroundImage.size().height() != 240 || backgroundImage.size().width() != 320)
		{
			ui.ErrorLabel->setText("Can't load image with size 320x240!!");
			return false;
		}
	}

	ui.ErrorLabel->setText("");
	return true;
}

void BackgroundPage::radioButtonClicked()
{
	if (ui.buttonGroup->checkedButton()->text() == "Default background")
	{
		ui.Background_lineEdit->setDisabled(true);
		ui.Browse_pushButton->setDisabled(true);
		ui.Background_lineEdit->setText("");
	}
	else if (ui.buttonGroup->checkedButton()->text() == "Custom background")
	{
		ui.Background_lineEdit->setDisabled(false);
		ui.Browse_pushButton->setDisabled(false);
	}
}

void BackgroundPage::browseButtonClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Select Background"), "/", tr("Images (*.png *.jpg)"));

	ui.Background_lineEdit->setText(fileName);

	validatePage();
}

QString BackgroundPage::getBackground()
{
	return ui.Background_lineEdit->text();
}

int BackgroundPage::nextId() const
{
	return Page::Page_Type;
}

QString BackgroundPage::getSuffix()
{
	QFileInfo oldFile(getBackground());

	return oldFile.completeSuffix();
}