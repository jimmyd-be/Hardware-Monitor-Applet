#include "GraphScreenWidget.h"

GraphScreenWidget::GraphScreenWidget(QString name, Logitech *, QWidget *parent)
	: QWidget(parent), name_(name)
{
	setupUi(this);
}


GraphScreenWidget::~GraphScreenWidget()
{
}