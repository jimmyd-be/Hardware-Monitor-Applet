#include "LineScreenWidget.h"
#include "NormalScreenWidget.h"

LineScreenWidget::LineScreenWidget(NormalScreenWidget * widget, QWidget *parent)
	: QWidget(parent), normalScreenWidget_(widget)
{
	setupUi(this);

	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeLine()));
}


LineScreenWidget::~LineScreenWidget()
{
}

void LineScreenWidget::removeLine()
{
	normalScreenWidget_->removeWidget(this);
}