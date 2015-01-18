#include "IntroPage.h"


IntroPage::IntroPage(QVector<Screen *> screenList, KeyboardTypes type, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenNames_(screenList), keyboardType_(type), oldPagename_("")
{
	setTitle(tr("Introduction"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);
}

IntroPage::IntroPage(QVector<Screen *> screenList, KeyboardTypes type, QString name, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), screenNames_(screenList), keyboardType_(type), oldPagename_(name)
{
	setTitle(tr("Introduction"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.ScreenName_lineEdit->setText(name);
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
	if (ui.ScreenName_lineEdit->text() != oldPagename_)
	{
		if (ui.ScreenName_lineEdit->text().isEmpty())
		{
			ui.Error_label->setText("You must fillin a screenname!!");

			return false;
		}

		for (Screen * screenData : screenNames_)
		{
			if (ui.ScreenName_lineEdit->text() == screenData->getName())
			{
				ui.Error_label->setText("Screenname must be unique!!");
				return false;
			}
		}
	}

	return true;
}

int IntroPage::nextId() const
{
	if (keyboardType_ == KeyboardTypes::Monochrome)
	{
		return Page::Page_Data;
	}
	/*else if (keyboardType_ == KeyboardTypes::Color)
	{
		return Page::Page_Background;
	}*/
	else
	{
		return Page::Page_Background;
	}
}

QString IntroPage::getPageName()
{
	return ui.ScreenName_lineEdit->text();
}