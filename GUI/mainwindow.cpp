#include "mainwindow.h"

MainWindow::MainWindow(Logitech * logitech,QWidget *parent)
    : QMainWindow(parent), logitech_(logitech), degreeGroup_(nullptr)
{
	ui.setupUi(this);

#ifdef __linux__
    ui.menuAutostart->setDisabled(true);
    ui.actionClose->setDisabled(true);
#endif

	createLanguageMenu();

	keyboardChanged(logitech->getKeyboardType());

	degreeGroup_ = new QActionGroup(this);
	degreeGroup_->addAction(ui.actionFahrenheit);
	degreeGroup_->addAction(ui.actionCelsius);

	autoStartGroup_ = new QActionGroup(this);
	autoStartGroup_->addAction(ui.actionEnable);
	autoStartGroup_->addAction(ui.actionDisable);

	if (HwaSettings::getInstance()->getTemperature() == TemperatureType::Fahrenheit)
	{
		ui.actionFahrenheit->setChecked(true);
	}

	ui.actionEnable->setChecked(HwaSettings::getInstance()->getAutoStart());
	ui.actionDisable->setChecked(!HwaSettings::getInstance()->getAutoStart());

	connect(ui.AddScreen_Button, SIGNAL(clicked()), this, SLOT(openScreenWizard()));
	connect(ui.Order_pushButton, SIGNAL(clicked()), this, SLOT(openOrderWindow()));
	connect(ui.actionClose, SIGNAL(triggered()), this, SLOT(closeWindow()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(closeProgram()));
	connect(ui.actionFahrenheit, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionCelsius, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionReport_a_bug, SIGNAL(triggered()), this, SLOT(reportIssue()));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(openAboutWindow()));
	connect(ui.actionEnable, SIGNAL(triggered()), this, SLOT(settingsChanged()));
	connect(ui.actionDisable, SIGNAL(triggered()), this, SLOT(settingsChanged()));
    connect(ui.actionChange_InfluxDb_settings, SIGNAL(triggered()), this, SLOT(openInfluxDialog()));

	fillinPages();
}

MainWindow::~MainWindow()
{
	removePages();

	if (degreeGroup_ != nullptr)
	{
		delete degreeGroup_;
		degreeGroup_ = nullptr;
	}

	if (autoStartGroup_ != nullptr)
	{
		delete autoStartGroup_;
		autoStartGroup_ = nullptr;
	}

}

void MainWindow::keyboardChanged(KeyboardTypes type)
{
	if (type == KeyboardTypes::None)
	{
		ui.statusBar->showMessage(tr("No Logitech keyboard found!!"));
	}
	else if (type == KeyboardTypes::Monochrome)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech monochrome (G15, G15s, G510) keyboard"));
	}
	else if (type == KeyboardTypes::Color)
	{
		ui.statusBar->showMessage(tr("Connected to: Logitech color (G19, G19s) keyboard"));
	}

	ui.statusBar->show();
}

void MainWindow::openInfluxDialog()
{
    InfluxDbDialog * dialog = new InfluxDbDialog();
    dialog->exec();

    delete dialog;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	closeWindow();
	event->ignore();
}

void MainWindow::closeWindow()
{
    //controller_->closeSettingsScreen();

#ifdef __linux__
    QApplication::quit();
#elif _WIN32
    hide();
#endif
}

void MainWindow::closeProgram()
{
    QApplication::quit();
    //controller_->quitApplication();
}

void MainWindow::reportIssue()
{
    QUrl url("https://github.com/lonelobo0070/Hardware-Monitor-Applet/issues");
	QDesktopServices::openUrl(url);
}

void MainWindow::openAboutWindow()
{
	AboutDialog * dialog = new AboutDialog();

	dialog->exec();

	delete dialog;
}

void MainWindow::openScreenWizard()
{
	CreateScreenWizard * wizard = new CreateScreenWizard(logitech_, this);
	wizard->exec();
	
	delete wizard;

	refreshPages();
}

void MainWindow::settingsChanged()
{
	if (ui.actionCelsius->isChecked())
	{
		HwaSettings::getInstance()->setTemperature(TemperatureType::Celsius);
	}
	else if (ui.actionFahrenheit->isChecked())
	{
		HwaSettings::getInstance()->setTemperature(TemperatureType::Fahrenheit);
	}

	if (ui.actionEnable->isChecked())
	{
		HwaSettings::getInstance()->setAutoStart(true);
	}
	else if (ui.actionDisable->isChecked())
	{
		HwaSettings::getInstance()->setAutoStart(false);
	}

}

void MainWindow::fillinPages()
{
	QList<Screen *> pages = sortScreenList(logitech_->getScreenList());

	for (int i = 0; i < pages.size(); i++)
	{
        MainScreenWidget * widget = new MainScreenWidget(logitech_, pages[i]->getName(), pages[i]->getScreenType(), logitech_->isScreenActive(pages[i]->getName()));

        connect(widget, SIGNAL(refreshMainWindow()), this, SLOT(refreshPages()));

		ui.ScreenList_Layout->addWidget(widget);

		widgetList_.append(widget);
	}
}

QList<Screen *> MainWindow::sortScreenList(QList<Screen*> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		int min = i;

		for (int j = i + 1; j < list.size(); j++)
		{
			QString test = list[min]->getName();
			QString test2 = list[j]->getName();

			if (QString::compare(list[min]->getName(), list[j]->getName(), Qt::CaseInsensitive) > 0)
			{
				min = j;
			}
		}

		Screen * temp = list[i];
		list[i] = list[min];
		list[min] = temp;
	}

	return list;
}

void MainWindow::removePages()
{
	for (QWidget * widget : widgetList_)
	{
		ui.ScreenList_Layout->removeWidget(widget);
		delete widget;
	}

	widgetList_.clear();
}

void MainWindow::refreshPages()
{
	removePages();
	fillinPages();
}


void MainWindow::openOrderWindow()
{
	OrderWindow * window = new OrderWindow(logitech_);

	window->exec();

	refreshPages();

	delete window;
}

void MainWindow::loadLanguage(const QString& rLanguage)
{
	if (m_currLang != rLanguage)
	{
		m_currLang = rLanguage;
		QLocale locale = QLocale(m_currLang);
		QLocale::setDefault(locale);
		QString languageName = QLocale::languageToString(locale.language());
		switchTranslator(m_translator, QString("HMA_%1.qm").arg(rLanguage));
		ui.statusBar->showMessage(tr("Current Language changed to %1").arg(languageName));

		HwaSettings::getInstance()->setLanguage(rLanguage);
	}
}

void MainWindow::switchTranslator(QTranslator& translator, const QString& filename)
{
	// remove the old translator
	qApp_->removeTranslator(&translator);

	// load the new translator
	if (translator.load(QApplication::applicationDirPath() + "/Languages/" + filename))
	{
		qApp_->installTranslator(&translator);
	}
}

// we create the menu entries dynamically, dependant on the existing translations.
void MainWindow::createLanguageMenu()
{
	QActionGroup* langGroup = new QActionGroup(ui.menuLanguage);
	langGroup->setExclusive(true);

	connect(langGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotLanguageChanged(QAction *)));

	QString defaultLocale = HwaSettings::getInstance()->getLanguage();
	
	// format systems language
	if (defaultLocale.isEmpty())
	{
		defaultLocale = QLocale::system().name();       // e.g. "de_DE"
		defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
	}

	m_langPath = QApplication::applicationDirPath();
	m_langPath.append("/Languages");
	QDir dir(m_langPath);
	QStringList fileNames = dir.entryList(QStringList("HMA_*.qm"));

	for (int i = 0; i < fileNames.size(); ++i)
	{
		// get locale extracted by filename
		QString locale;
		locale = fileNames[i];                  // "TranslationExample_de.qm"
		locale.truncate(locale.lastIndexOf('.'));   // "TranslationExample_de"
		locale.remove(0, locale.indexOf('_') + 1);   // "de"

		QString lang = QLocale::languageToString(QLocale(locale).language());
		QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

		QAction *action = new QAction(ico, lang, this);
		action->setCheckable(true);
		action->setData(locale);

		ui.menuLanguage->addAction(action);
		langGroup->addAction(action);

		// set default translators and language checked
		if (defaultLocale == locale)
		{
			action->setChecked(true);
			slotLanguageChanged(action);
		}
	}

	connect(langGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotLanguageChanged(QAction *)));
}

// Called every time, when a menu entry of the language menu is called
void MainWindow::slotLanguageChanged(QAction* action)
{
	if (0 != action)
	{
		// load the language dependant on the action content
		loadLanguage(action->data().toString());
	}
}

void MainWindow::changeEvent(QEvent* event)
{
	if (0 != event)
	{
		switch (event->type())
		{
			// this event is send if a translator is loaded
		case QEvent::LanguageChange:
			ui.retranslateUi(this);
			break;
			// this event is send, if the system, language changes
		case QEvent::LocaleChange:
		{
			QString locale = QLocale::system().name();
			locale.truncate(locale.lastIndexOf('_'));
			loadLanguage(locale);
		}
		break;
		}
	}

	QMainWindow::changeEvent(event);
}
