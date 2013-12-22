/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMonochrome;
    QAction *actionColor;
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionBackup_settings;
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionReport_issue;
    QAction *actionLoad_default_settings;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QRadioButton *monochromeRadioButton;
    QRadioButton *colorRadioButton;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFontComboBox *fontComboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *fontSpinBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *backgroundHorizontalLayout;
    QLabel *label_3;
    QLineEdit *browseLine;
    QPushButton *browseButton;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *saveButton;
    QPushButton *undoButton;
    QPushButton *saveRestartButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *keyboardGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(568, 570);
        actionMonochrome = new QAction(MainWindow);
        actionMonochrome->setObjectName(QStringLiteral("actionMonochrome"));
        actionMonochrome->setCheckable(true);
        actionColor = new QAction(MainWindow);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        actionColor->setCheckable(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionBackup_settings = new QAction(MainWindow);
        actionBackup_settings->setObjectName(QStringLiteral("actionBackup_settings"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionReport_issue = new QAction(MainWindow);
        actionReport_issue->setObjectName(QStringLiteral("actionReport_issue"));
        actionLoad_default_settings = new QAction(MainWindow);
        actionLoad_default_settings->setObjectName(QStringLiteral("actionLoad_default_settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        monochromeRadioButton = new QRadioButton(centralWidget);
        keyboardGroup = new QButtonGroup(MainWindow);
        keyboardGroup->setObjectName(QStringLiteral("keyboardGroup"));
        keyboardGroup->addButton(monochromeRadioButton);
        monochromeRadioButton->setObjectName(QStringLiteral("monochromeRadioButton"));

        horizontalLayout_4->addWidget(monochromeRadioButton);

        colorRadioButton = new QRadioButton(centralWidget);
        keyboardGroup->addButton(colorRadioButton);
        colorRadioButton->setObjectName(QStringLiteral("colorRadioButton"));
        colorRadioButton->setChecked(true);

        horizontalLayout_4->addWidget(colorRadioButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        fontComboBox = new QFontComboBox(centralWidget);
        fontComboBox->setObjectName(QStringLiteral("fontComboBox"));

        horizontalLayout->addWidget(fontComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        fontSpinBox = new QSpinBox(centralWidget);
        fontSpinBox->setObjectName(QStringLiteral("fontSpinBox"));
        fontSpinBox->setValue(8);

        horizontalLayout->addWidget(fontSpinBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        backgroundHorizontalLayout = new QHBoxLayout();
        backgroundHorizontalLayout->setSpacing(6);
        backgroundHorizontalLayout->setObjectName(QStringLiteral("backgroundHorizontalLayout"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        backgroundHorizontalLayout->addWidget(label_3);

        browseLine = new QLineEdit(centralWidget);
        browseLine->setObjectName(QStringLiteral("browseLine"));

        backgroundHorizontalLayout->addWidget(browseLine);

        browseButton = new QPushButton(centralWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        backgroundHorizontalLayout->addWidget(browseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        backgroundHorizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(backgroundHorizontalLayout, 2, 0, 1, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);

        gridLayout->addWidget(tabWidget, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout_3->addWidget(saveButton);

        undoButton = new QPushButton(centralWidget);
        undoButton->setObjectName(QStringLiteral("undoButton"));

        horizontalLayout_3->addWidget(undoButton);

        saveRestartButton = new QPushButton(centralWidget);
        saveRestartButton->setObjectName(QStringLiteral("saveRestartButton"));

        horizontalLayout_3->addWidget(saveRestartButton);


        gridLayout->addLayout(horizontalLayout_3, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 568, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad_default_settings);
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionReport_issue);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OHM Applet Settings", 0));
        actionMonochrome->setText(QApplication::translate("MainWindow", "Monochrome", 0));
        actionColor->setText(QApplication::translate("MainWindow", "Color", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionBackup_settings->setText(QApplication::translate("MainWindow", "Backup settings", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0));
        actionReport_issue->setText(QApplication::translate("MainWindow", "Report issue", 0));
        actionLoad_default_settings->setText(QApplication::translate("MainWindow", "Load default settings", 0));
        label_4->setText(QApplication::translate("MainWindow", "Keyboard:", 0));
        monochromeRadioButton->setText(QApplication::translate("MainWindow", "Monochrome (G15, G510, ...)", 0));
        colorRadioButton->setText(QApplication::translate("MainWindow", "Color (G19)", 0));
        label->setText(QApplication::translate("MainWindow", "Font:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Font size:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Main background:", 0));
        browseButton->setText(QApplication::translate("MainWindow", "Browse", 0));
        saveButton->setText(QApplication::translate("MainWindow", "Save", 0));
        undoButton->setText(QApplication::translate("MainWindow", "Undo changes", 0));
        saveRestartButton->setText(QApplication::translate("MainWindow", "Save and restart Applet", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H