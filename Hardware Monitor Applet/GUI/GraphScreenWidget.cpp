#include "GraphScreenWidget.h"

GraphScreenWidget::GraphScreenWidget(QString name, QWidget *parent)
	: QWidget(parent), name_(name)
{
	setupUi(this);
}


GraphScreenWidget::~GraphScreenWidget()
{
}