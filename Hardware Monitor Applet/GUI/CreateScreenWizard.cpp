#include "CreateScreenWizard.h"

CreateScreenWizard::CreateScreenWizard(Logitech * logitech, QWidget *parent)
	: QWizard(parent, Qt::Dialog), logitech_(logitech), oldPageName_(""),
	introPage_(nullptr), backgroundPage_(nullptr), screenTypePage_(nullptr), dataPage_(nullptr), lineEditPage_(nullptr), graphPage_(nullptr), customizePage_(nullptr)
{
	introPage_ = new IntroPage(logitech_->getScreenList(), logitech_->getKeyboardType());
	backgroundPage_ = new BackgroundPage();
	screenTypePage_ = new ScreenTypePage();
	dataPage_ = new DataPage(screenTypePage_);
	lineEditPage_ = new LineEditPage(dataPage_);	
	customizePage_ = new CustomizePage(lineEditPage_);
	graphPage_ = new GraphPage(dataPage_);

	setPage(Page_Intro, introPage_);
	setPage(Page_Background, backgroundPage_);
	setPage(Page_Type, screenTypePage_);
	setPage(Page_Data, dataPage_);
	setPage(Page_LineEdit, lineEditPage_);
	setPage(Page_GraphEdit, graphPage_);
	setPage(Page_Customize, customizePage_);

	setWindowTitle(tr("Screen Wizard"));
}

CreateScreenWizard::CreateScreenWizard(Logitech * logitech, QString name, QWidget *parent)
	: QWizard(parent, Qt::Dialog), logitech_(logitech), oldPageName_(name),
	introPage_(nullptr), backgroundPage_(nullptr), screenTypePage_(nullptr), dataPage_(nullptr), lineEditPage_(nullptr), graphPage_(nullptr), customizePage_(nullptr)
{
	Screen * oldScreen = logitech_->getScreenData(oldPageName_);

	introPage_ = new IntroPage(logitech_->getScreenList(), logitech_->getKeyboardType(), oldPageName_);
	backgroundPage_ = new BackgroundPage(oldScreen->getBackground());
	screenTypePage_ = new ScreenTypePage(oldScreen->getScreenType());

	if (oldScreen->getScreenType() == ScreenType::Normal)
	{
		NormalScreen * oldNormalScreen = (NormalScreen*)oldScreen;
		dataPage_ = new DataPage(screenTypePage_, oldNormalScreen->getLines());
		lineEditPage_ = new LineEditPage(dataPage_, oldNormalScreen->getLines());
		customizePage_ = new CustomizePage(lineEditPage_);

		setPage(Page_Data, dataPage_);
		setPage(Page_LineEdit, lineEditPage_);
		setPage(Page_Customize, customizePage_);
	}
	else if (oldScreen->getScreenType() == ScreenType::Graph)
	{
		//graphPage_ = new GraphPage(dataPage_, oldScreen->getLines(), oldScreen->getGraphColors());
		//setPage(Page_GraphEdit, graphPage_);
	}

	setPage(Page_Intro, introPage_);
	setPage(Page_Background, backgroundPage_);
	setPage(Page_Type, screenTypePage_);

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
	if (!oldPageName_.isEmpty())
	{
		logitech_->deleteScreen(oldPageName_);
	}

	QString background = "";

	if (!backgroundPage_->getBackground().isEmpty())
	{
		copyBackground();

		background = introPage_->getPageName() + "." + backgroundPage_->getSuffix();
	}

	if (screenTypePage_->getScreenType() == ScreenType::Normal)
	{
		logitech_->createNormalScreen(introPage_->getPageName(), background, screenTypePage_->getScreenType(), dataPage_->getData(), lineEditPage_->getData(), customizePage_->getData());
	}

	else if (screenTypePage_->getScreenType() == ScreenType::Graph)
	{
		logitech_->creategraphScreen(introPage_->getPageName(), background, screenTypePage_->getScreenType(), graphPage_->getValues(), graphPage_->getColors());
	}

	Settings::getInstance()->saveSettings();

	QDialog::accept();
}

void CreateScreenWizard::copyBackground()
{
	QFileInfo oldFile(backgroundPage_->getBackground());

	QString newDir = Defines::getSettingsFolder() + "/Background";
	QString newFile = newDir + "/" + introPage_->getPageName() + "." + oldFile.completeSuffix();

	QDir dir(newDir);

	if (!dir.exists())
	{
		dir.mkpath(dir.filePath(newDir));
	}

	QFile backgroundFile(newFile);

	if (backgroundFile.exists())
	{
		backgroundFile.remove();
	}

	QFile::copy(backgroundPage_->getBackground(), newFile);
}