#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "../Defines.h"
#include "../Logitech.h"
#include "SortScreenDialog.h"
#include "MainScreenWidget.h"
#include "../Settings.h"
#include "OrderWindow.h"
#include <QDesktopServices>
#include <QScrollArea>
#include "AboutDialog.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    MainWindow(Logitech * logitech, QWidget *parent = 0);
	~MainWindow();

	void keyboardChanged(KeyboardTypes);

public slots:
	void refreshPages();

protected:
	void closeEvent(QCloseEvent * event);

private:
	void fillinPages();
	void removePages();
	QList<Screen *> sortScreenList(QList<Screen*>);

	void loadLanguage(const QString& rLanguage);
	void createLanguageMenu();
	void switchTranslator(QTranslator& translator, const QString& filename);
	void changeEvent(QEvent*);
	
	Ui::MainWindowClass ui;
	Logitech * logitech_;
	QApplication * qApp_;
	QVector<MainScreenWidget *> widgetList_;
	QActionGroup * degreeGroup_;
	QActionGroup * autoStartGroup_;

	QTranslator     m_translator;   /**< contains the translations for this application */
	QTranslator     m_translatorQt; /**< contains the translations for qt */
	QString         m_currLang;     /**< contains the currently loaded language */
	QString         m_langPath;     /**< Path of language files. This is always fixed to /languages. */

private slots:
	void openScreenWizard();
	void openOrderWindow();
	void closeProgram();
	void closeWindow();
	void settingsChanged();
	void reportIssue();
	void openAboutWindow();

	void slotLanguageChanged(QAction* action);
}; 

#endif // MAINWINDOW_H
