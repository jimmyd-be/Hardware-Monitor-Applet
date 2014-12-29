#include "CreateScreenWizard.h"

CreateScreenWizard::CreateScreenWizard(QWidget *parent)
	: QWizard(parent, Qt::Dialog)
{
	dataPage_ = new DataPage();
	lineEditPage_ = new LineEditPage(dataPage_);
	introPage_ = new IntroPage(/*Add list of screenNames*//*Add logitech keyboard type*/);
	backgroundPage_ = new BackgroundPage();
	screenTypePage_ = new ScreenTypePage();
	customizePage_ = new CustomizePage(lineEditPage_);

	setPage(Page_Intro, introPage_);
	setPage(Page_Background, backgroundPage_);
	setPage(Page_Type, screenTypePage_);
	setPage(Page_Data, dataPage_);
	setPage(Page_LineEdit, lineEditPage_);
	//	addPage(Page_GraphEdit, new ConclusionPage);
	setPage(Page_Customize, customizePage_);

	setWindowTitle(tr("Screen Wizard"));
}

CreateScreenWizard::~CreateScreenWizard()
{
}

/*void CreateScreenWizard::accept()
{
	QByteArray className = field("className").toByteArray();
	QByteArray baseClass = field("baseClass").toByteArray();
	QByteArray macroName = field("macroName").toByteArray();
	QByteArray baseInclude = field("baseInclude").toByteArray();

	QString outputDir = field("outputDir").toString();
	QString header = field("header").toString();
	QString implementation = field("implementation").toString();
	QDialog::accept();
}*/