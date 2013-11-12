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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFontComboBox *fontComboBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *browseLine;
    QPushButton *browseButton;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuKeyboard;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

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
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
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

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout->addWidget(spinBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        browseLine = new QLineEdit(centralWidget);
        browseLine->setObjectName(QStringLiteral("browseLine"));

        horizontalLayout_2->addWidget(browseLine);

        browseButton = new QPushButton(centralWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout_2->addWidget(browseButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 568, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuKeyboard = new QMenu(menuBar);
        menuKeyboard->setObjectName(QStringLiteral("menuKeyboard"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuKeyboard->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad_default_settings);
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionReport_issue);
        menuHelp->addAction(actionHelp);
        menuKeyboard->addAction(actionMonochrome);
        menuKeyboard->addAction(actionColor);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionMonochrome->setText(QApplication::translate("MainWindow", "Monochrome", 0));
        actionColor->setText(QApplication::translate("MainWindow", "Color", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionBackup_settings->setText(QApplication::translate("MainWindow", "Backup settings", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0));
        actionReport_issue->setText(QApplication::translate("MainWindow", "Report issue", 0));
        actionLoad_default_settings->setText(QApplication::translate("MainWindow", "Load default settings", 0));
        label->setText(QApplication::translate("MainWindow", "Font:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Font size:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Main background:", 0));
        browseButton->setText(QApplication::translate("MainWindow", "Browse", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Save", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Reset settings", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuKeyboard->setTitle(QApplication::translate("MainWindow", "Keyboard", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
