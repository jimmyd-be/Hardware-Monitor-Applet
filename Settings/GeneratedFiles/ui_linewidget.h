/********************************************************************************
** Form generated from reading UI file 'linewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEWIDGET_H
#define UI_LINEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LineWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *AddDataButton;
    QPushButton *removeLineButton;

    void setupUi(QWidget *LineWidget)
    {
        if (LineWidget->objectName().isEmpty())
            LineWidget->setObjectName(QStringLiteral("LineWidget"));
        LineWidget->resize(532, 70);
        horizontalLayout = new QHBoxLayout(LineWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(LineWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(LineWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        AddDataButton = new QPushButton(LineWidget);
        AddDataButton->setObjectName(QStringLiteral("AddDataButton"));

        horizontalLayout->addWidget(AddDataButton);

        removeLineButton = new QPushButton(LineWidget);
        removeLineButton->setObjectName(QStringLiteral("removeLineButton"));

        horizontalLayout->addWidget(removeLineButton);


        retranslateUi(LineWidget);

        QMetaObject::connectSlotsByName(LineWidget);
    } // setupUi

    void retranslateUi(QWidget *LineWidget)
    {
        LineWidget->setWindowTitle(QApplication::translate("LineWidget", "Form", 0));
        label->setText(QApplication::translate("LineWidget", "Line 1:", 0));
        AddDataButton->setText(QApplication::translate("LineWidget", "Add data", 0));
        removeLineButton->setText(QApplication::translate("LineWidget", "Remove line", 0));
    } // retranslateUi

};

namespace Ui {
    class LineWidget: public Ui_LineWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEWIDGET_H
