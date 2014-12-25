#include "CreateScreenWizard.h"

CreateScreenWizard::CreateScreenWizard(QWidget *parent)
	: QWizard(parent, Qt::Dialog)
{
	setPage(Page_Intro, new IntroPage(/*Add list of screenNames*/));
	//setPage(Page_Background, new BackbroudPage());
	setPage(Page_Type, new ScreenTypePage(/*Add logitech keyboard type*/));
	setPage(Page_Data, new DataPage());
	/*addPage(Page_LineEdit, new OutputFilesPage);
	addPage(Page_GraphEdit, new ConclusionPage);
	addPage(Page_Customize, new ConclusionPage);

	setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
	setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));
	*/
	setWindowTitle(tr("SCreen Wizard"));
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