#include "LineScreenWidget.h"
#include "NormalScreenWidget.h"

LineScreenWidget::LineScreenWidget(NormalScreenWidget * widget, QWidget *parent)
	: QWidget(parent), normalScreenWidget_(widget)
{
	setupUi(this);

	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeLine()));
	connect(lineText, SIGNAL(textEdited(QString)), this, SLOT(textChanged(QString)));
}

LineScreenWidget::LineScreenWidget(QString text, NormalScreenWidget * widget, QWidget *parent)
	: QWidget(parent), normalScreenWidget_(widget)
{
	setupUi(this);

	lineText->setText(text);

	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeLine()));
	connect(lineText, SIGNAL(textEdited(QString)), this, SLOT(textChanged(QString)));
}


LineScreenWidget::~LineScreenWidget()
{
}

void LineScreenWidget::removeLine()
{
	normalScreenWidget_->removeWidget(this);
}

QString LineScreenWidget::getText()
{
	return lineText->text();
}

void LineScreenWidget::textChanged(QString text)
{
	normalScreenWidget_->lineScreenTextChanged();
}