#include "CreateScreenWizard.h"

CreateScreenWizard::CreateScreenWizard(Logitech * logitech, QWidget *parent)
	: QWizard(parent, Qt::Dialog), logitech_(logitech)
{
	introPage_ = new IntroPage(logitech_->getScreenList(), logitech_->getKeyboardType());
	backgroundPage_ = new BackgroundPage();
	screenTypePage_ = new ScreenTypePage();
	dataPage_ = new DataPage(screenTypePage_->getScreenType());
	lineEditPage_ = new LineEditPage(dataPage_);	
	customizePage_ = new CustomizePage(lineEditPage_);
	graphPage_ = new GraphPage(lineEditPage_);

	setPage(Page_Intro, introPage_);
	setPage(Page_Background, backgroundPage_);
	setPage(Page_Type, screenTypePage_);
	setPage(Page_Data, dataPage_);
	setPage(Page_LineEdit, lineEditPage_);
	setPage(Page_GraphEdit, graphPage_);
	setPage(Page_Customize, customizePage_);

	setWindowTitle(tr("Screen Wizard"));
}

CreateScreenWizard::~CreateScreenWizard()
{
	if (introPage_ != nullptr)
	{
		delete introPage_;
		introPage_ = nullptr;
	}

	if (backgroundPage_ != nullptr)
	{
		delete backgroundPage_;
		backgroundPage_ = nullptr;
	}

	if (screenTypePage_ != nullptr)
	{
		delete screenTypePage_;
		screenTypePage_ = nullptr;
	}

	if (dataPage_ != nullptr)
	{
		delete dataPage_;
		dataPage_ = nullptr;
	}

	if (lineEditPage_ != nullptr)
	{
		delete lineEditPage_;
		lineEditPage_ = nullptr;
	}

	if (customizePage_ != nullptr)
	{
		delete customizePage_;
		customizePage_ = nullptr;
	}

	if (graphPage_ != nullptr)
	{
		delete graphPage_;
		graphPage_ = nullptr;
	}
}

void CreateScreenWizard::accept()
{
	QByteArray className = field("className").toByteArray();
	QByteArray baseClass = field("baseClass").toByteArray();
	QByteArray macroName = field("macroName").toByteArray();
	QByteArray baseInclude = field("baseInclude").toByteArray();

	QString outputDir = field("outputDir").toString();
	QString header = field("header").toString();
	QString implementation = field("implementation").toString();
	QDialog::accept();
}
