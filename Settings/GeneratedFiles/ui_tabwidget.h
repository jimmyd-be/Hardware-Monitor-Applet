/********************************************************************************
** Form generated from reading UI file 'tabwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABWIDGET_H
#define UI_TABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *addLineButton;
    QPushButton *removePageButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *TabWidget)
    {
        if (TabWidget->objectName().isEmpty())
            TabWidget->setObjectName(QStringLiteral("TabWidget"));
        TabWidget->resize(406, 223);
        verticalLayout = new QVBoxLayout(TabWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        addLineButton = new QPushButton(TabWidget);
        addLineButton->setObjectName(QStringLiteral("addLineButton"));

        horizontalLayout_5->addWidget(addLineButton);

        removePageButton = new QPushButton(TabWidget);
        removePageButton->setObjectName(QStringLiteral("removePageButton"));

        horizontalLayout_5->addWidget(removePageButton);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 140, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(TabWidget);

        QMetaObject::connectSlotsByName(TabWidget);
    } // setupUi

    void retranslateUi(QWidget *TabWidget)
    {
        TabWidget->setWindowTitle(QApplication::translate("TabWidget", "Form", 0));
        addLineButton->setText(QApplication::translate("TabWidget", "Add line", 0));
        removePageButton->setText(QApplication::translate("TabWidget", "Remove page", 0));
    } // retranslateUi

};

namespace Ui {
    class TabWidget: public Ui_TabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABWIDGET_H
