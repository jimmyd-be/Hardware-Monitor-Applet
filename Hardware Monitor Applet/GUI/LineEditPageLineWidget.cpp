#include "LineEditPageLineWidget.h"


LineEditPageLineWidget::LineEditPageLineWidget(QString text, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.lineEdit->setText(text);

	QShortcut pasteShortcut(QKeySequence(tr("Ctrl+V")), ui.lineEdit);
	QShortcut cutShortcut(QKeySequence(tr("Ctrl+X")), ui.lineEdit);
	QShortcut copyShortcut(QKeySequence(tr("Ctrl+C")), ui.lineEdit);

	connect(&copyShortcut, SIGNAL(activated()), ui.lineEdit, SLOT(copy()));
	connect(&cutShortcut, SIGNAL(activated()), ui.lineEdit, SLOT(cut()));
	connect(&pasteShortcut, SIGNAL(activated()), ui.lineEdit, SLOT(paste()));

}

LineEditPageLineWidget::~LineEditPageLineWidget()
{

}

QString LineEditPageLineWidget::getText()
{
	return ui.lineEdit->text();
}