/********************************************************************************
** Form generated from reading UI file 'datawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAWINDOW_H
#define UI_DATAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DataWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *hardWareTableWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *sensorTableWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *hardwarePushButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *sensorPushButton;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DataWindow)
    {
        if (DataWindow->objectName().isEmpty())
            DataWindow->setObjectName(QStringLiteral("DataWindow"));
        DataWindow->resize(731, 694);
        verticalLayout_2 = new QVBoxLayout(DataWindow);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(DataWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_2 = new QLabel(DataWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        label_3 = new QLabel(DataWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        hardWareTableWidget = new QTableWidget(DataWindow);
        if (hardWareTableWidget->columnCount() < 2)
            hardWareTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        hardWareTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        hardWareTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        hardWareTableWidget->setObjectName(QStringLiteral("hardWareTableWidget"));
        hardWareTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        hardWareTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        horizontalLayout_8->addWidget(hardWareTableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        sensorTableWidget = new QTableWidget(DataWindow);
        if (sensorTableWidget->columnCount() < 5)
            sensorTableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        sensorTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        sensorTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        sensorTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        sensorTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        sensorTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem6);
        sensorTableWidget->setObjectName(QStringLiteral("sensorTableWidget"));
        sensorTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sensorTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout->addWidget(sensorTableWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(DataWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        spinBox = new QSpinBox(DataWindow);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout_4->addWidget(spinBox);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_8->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        hardwarePushButton = new QPushButton(DataWindow);
        hardwarePushButton->setObjectName(QStringLiteral("hardwarePushButton"));

        horizontalLayout->addWidget(hardwarePushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        sensorPushButton = new QPushButton(DataWindow);
        sensorPushButton->setObjectName(QStringLiteral("sensorPushButton"));

        horizontalLayout_2->addWidget(sensorPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        lineEdit = new QLineEdit(DataWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(DataWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox);


        retranslateUi(DataWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), DataWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DataWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(DataWindow);
    } // setupUi

    void retranslateUi(QDialog *DataWindow)
    {
        DataWindow->setWindowTitle(QApplication::translate("DataWindow", "Dialog", 0));
        label->setText(QApplication::translate("DataWindow", "Select data and press 'Add code' to add the data to the line!!", 0));
        label_2->setText(QApplication::translate("DataWindow", "Hardware", 0));
        label_3->setText(QApplication::translate("DataWindow", "Sensors", 0));
        QTableWidgetItem *___qtablewidgetitem = hardWareTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DataWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = hardWareTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DataWindow", "HardwareType", 0));
        QTableWidgetItem *___qtablewidgetitem2 = sensorTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("DataWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem3 = sensorTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("DataWindow", "SensorType", 0));
        QTableWidgetItem *___qtablewidgetitem4 = sensorTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("DataWindow", "Max", 0));
        QTableWidgetItem *___qtablewidgetitem5 = sensorTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("DataWindow", "Min", 0));
        QTableWidgetItem *___qtablewidgetitem6 = sensorTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("DataWindow", "Value", 0));
        label_4->setText(QApplication::translate("DataWindow", "Round:", 0));
        hardwarePushButton->setText(QApplication::translate("DataWindow", "Add code", 0));
        sensorPushButton->setText(QApplication::translate("DataWindow", "Add code", 0));
    } // retranslateUi

};

namespace Ui {
    class DataWindow: public Ui_DataWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAWINDOW_H
