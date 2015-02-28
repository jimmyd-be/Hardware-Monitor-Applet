#include "LineEditPageLineWidget.h"


LineEditPageLineWidget::LineEditPageLineWidget(QString text, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.lineEdit->setText(text);
}

LineEditPageLineWidget::~LineEditPageLineWidget()
{

}

QString LineEditPageLineWidget::getText()
{
	return ui.lineEdit->text();
}