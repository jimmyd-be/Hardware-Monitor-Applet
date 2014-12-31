#include "OrderWindow.h"


OrderWindow::OrderWindow(Logitech * logitech, QWidget *parent)
	: QDialog(parent), logitech_(logitech)
{
	ui.setupUi(this);

	fillinCreatedScreenList();
}

OrderWindow::~OrderWindow()
{
}

void OrderWindow::fillinCreatedScreenList()
{
	QVector<Screen*> screenList = logitech_->getScreenList();

	for (Screen * screen : screenList)
	{
	//	ui.CreatedScreen_listWidget->addItem(screen->getName());
	}
}