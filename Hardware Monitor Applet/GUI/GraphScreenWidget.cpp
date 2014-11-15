#include "GraphScreenWidget.h"

GraphScreenWidget::GraphScreenWidget(QString name, Logitech *, QWidget *parent)
	: QWidget(parent), name_(name)
{
	setupUi(this);
}

GraphScreenWidget::GraphScreenWidget(Screen * data, Logitech *, QWidget *parent)
	: QWidget(parent), name_(data->getName())
{
	setupUi(this);
}


GraphScreenWidget::~GraphScreenWidget()
{
}