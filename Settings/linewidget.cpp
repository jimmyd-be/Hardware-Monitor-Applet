#include "linewidget.h"
#include "ui_linewidget.h"
#include "tabwidget.h"

LineWidget::LineWidget(WMI* wmi, TabWidget * tabWidget, int id, QWidget *parent) :
    wmi_(wmi), tabWidget_(tabWidget), id_(id), QWidget(parent),
    ui(new Ui::LineWidget)
{
    ui->setupUi(this);

    QString lineName = "Line ";
    lineName.append(QString::number(id));

    ui->label->setText(lineName);

    connect(ui->removeLineButton, SIGNAL(clicked()), this, SLOT(removeLine()));
	connect(ui->AddDataButton, SIGNAL(clicked()), this, SLOT(openDataWindow()));
}

LineWidget::~LineWidget()
{
    delete ui;
}

void LineWidget::removeLine()
{
    tabWidget_->removeLine(this);
}

int LineWidget::getId()
{
    return id_;
}

void LineWidget::setId(int id)
{
    id_ = id;

    QString lineName = "Line ";
    lineName.append(QString::number(id));

    ui->label->setText(lineName);
}

void LineWidget::openDataWindow()
{
	DataWindow window(wmi_, ui->lineEdit->text());
	window.exec();

	if(window.getLinetext() != "")
	{
		ui->lineEdit->setText(window.getLinetext());
	}
}

QString LineWidget::getText()
{
	return ui->lineEdit->text();
}

void LineWidget::setText(QString text)
{
	ui->lineEdit->setText(text);
}