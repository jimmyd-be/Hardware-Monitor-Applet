#include "OrderWindow.h"


OrderWindow::OrderWindow(Logitech * logitech, QWidget *parent)
	: QDialog(parent), logitech_(logitech)
{
	ui.setupUi(this);

	ui.AddSub_pushButton->setDisabled(true);
	ui.RemoveSub_pushButton->setDisabled(true);
	ui.LeftSub_pushButton->setDisabled(true);
	ui.RightSub_pushButton->setDisabled(true);

	connect(ui.AddMain_pushButton, SIGNAL(clicked()), this, SLOT(addMainButtonClicked()));
	connect(ui.MainTrack_listWidget, SIGNAL(itemSelectionChanged()), this, SLOT(mainListSelectionChanged()));
	connect(ui.RemoveMain_pushButton, SIGNAL(clicked()), this, SLOT(removeMainButtonClicked()));

	connect(ui.LeftMain_pushButton, SIGNAL(clicked()), this, SLOT(leftMainButtonClicked()));
	connect(ui.RightMain_pushButton, SIGNAL(clicked()), this, SLOT(rightMainButtonClicked()));

	connect(ui.AddSub_pushButton, SIGNAL(clicked()), this, SLOT(addSubButtonClicked()));
	connect(ui.RemoveSub_pushButton, SIGNAL(clicked()), this, SLOT(removeSubButtonClicked()));

	connect(ui.LeftSub_pushButton, SIGNAL(clicked()), this, SLOT(leftSubButtonClicked()));
	connect(ui.RightSub_pushButton, SIGNAL(clicked()), this, SLOT(rightSubButtonClicked()));

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	
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
		ui.CreatedScreen_listWidget->addItem(screen->getName());
	}
}

void OrderWindow::addMainButtonClicked()
{
	QList<QListWidgetItem*> items = ui.CreatedScreen_listWidget->selectedItems();

	for (QListWidgetItem * selected : items)
	{
		if (!subOrder_.contains(selected->text()))
		{
			ui.MainTrack_listWidget->addItem(selected->text());

			QList<QString> itemList;
			itemList.append(selected->text());

			subOrder_.insert(selected->text(), itemList);
		}
	}
}

void OrderWindow::mainListSelectionChanged()
{
	ui.SubTrack_listWidget->clear();

	QList<QListWidgetItem*> items = ui.MainTrack_listWidget->selectedItems();

	if (items.size() > 0)
	{
		ui.AddSub_pushButton->setDisabled(false);
		ui.RemoveSub_pushButton->setDisabled(false);
		ui.LeftSub_pushButton->setDisabled(false);
		ui.RightSub_pushButton->setDisabled(false);

		QList<QString> subItems = subOrder_.value(items[0]->text());

		for (QString name : subItems)
		{
			ui.SubTrack_listWidget->addItem(name);
		}
	}
	else
	{
		ui.AddSub_pushButton->setDisabled(true);
		ui.RemoveSub_pushButton->setDisabled(true);
		ui.LeftSub_pushButton->setDisabled(true);
		ui.RightSub_pushButton->setDisabled(true);
	}
}

void OrderWindow::removeMainButtonClicked()
{
	QList<QListWidgetItem*> items = ui.MainTrack_listWidget->selectedItems();

	for (QListWidgetItem * selected : items)
	{
		subOrder_.remove(selected->text());

		ui.MainTrack_listWidget->removeItemWidget(selected);
		delete selected;
	}
}

void OrderWindow::leftMainButtonClicked()
{
	int currentRow = ui.MainTrack_listWidget->currentRow();
	int previousRow = currentRow - 1;

	if (previousRow >= 0)
	{
		QListWidgetItem* itemOne = ui.MainTrack_listWidget->takeItem(currentRow);
		QListWidgetItem* itemTwo = ui.MainTrack_listWidget->takeItem(previousRow);

		ui.MainTrack_listWidget->insertItem(currentRow, itemTwo);
		ui.MainTrack_listWidget->insertItem(previousRow, itemOne);
	}
}

void OrderWindow::rightMainButtonClicked()
{
	int currentRow = ui.MainTrack_listWidget->currentRow();
	int nextRow = currentRow + 1;

	if (nextRow < ui.MainTrack_listWidget->count())
	{
		QListWidgetItem* itemOne = ui.MainTrack_listWidget->takeItem(currentRow);
		QListWidgetItem* itemTwo = ui.MainTrack_listWidget->takeItem(nextRow);

		ui.MainTrack_listWidget->insertItem(currentRow, itemTwo);
		ui.MainTrack_listWidget->insertItem(nextRow, itemOne);
	}
}


void OrderWindow::addSubButtonClicked()
{
	QList<QListWidgetItem*> items = ui.CreatedScreen_listWidget->selectedItems();

	QString mainPageName = ui.MainTrack_listWidget->selectedItems()[0]->text();

	for (QListWidgetItem * selected : items)
	{
		if (selected->text() != mainPageName)
		{
			ui.SubTrack_listWidget->addItem(selected->text());

			QList<QString> items = subOrder_.value(mainPageName);
			items.append(selected->text());

			subOrder_.remove(mainPageName);

			subOrder_.insert(mainPageName, items);
		}
	}
}

void OrderWindow::removeSubButtonClicked()
{
	QList<QListWidgetItem*> subItems = ui.SubTrack_listWidget->selectedItems();
	QList<QListWidgetItem*> mainItems = ui.MainTrack_listWidget->selectedItems();

	for (QListWidgetItem * selected : subItems)
	{
		if (selected->text() != mainItems[0]->text())
		{
			QList<QString> items = subOrder_.value(mainItems[0]->text());
			items.removeAt(items.indexOf(selected->text()));

			subOrder_.remove(mainItems[0]->text());

			subOrder_.insert(mainItems[0]->text(), items);

			ui.SubTrack_listWidget->removeItemWidget(selected);
			delete selected;
		}
	}
}

void OrderWindow::leftSubButtonClicked()
{
	int currentRow = ui.SubTrack_listWidget->currentRow();
	int previousRow = currentRow - 1;

	if (previousRow >= 0)
	{
		QListWidgetItem* itemOne = ui.SubTrack_listWidget->takeItem(currentRow);
		QListWidgetItem* itemTwo = ui.SubTrack_listWidget->takeItem(previousRow);

		ui.SubTrack_listWidget->insertItem(currentRow, itemTwo);
		ui.SubTrack_listWidget->insertItem(previousRow, itemOne);
	}

	QString mainpage = ui.MainTrack_listWidget->selectedItems()[0]->text();

	QList<QString> itemList;
	subOrder_.remove(mainpage);

	for (int i = 0; i < ui.SubTrack_listWidget->count(); i++)
	{
		itemList.append(ui.SubTrack_listWidget->item(i)->text());
	}

	subOrder_.insert(mainpage, itemList);
}

void OrderWindow::rightSubButtonClicked()
{
	int currentRow = ui.SubTrack_listWidget->currentRow();
	int nextRow = currentRow + 1;

	if (nextRow < ui.SubTrack_listWidget->count())
	{
		QListWidgetItem* itemOne = ui.SubTrack_listWidget->takeItem(currentRow);
		QListWidgetItem* itemTwo = ui.SubTrack_listWidget->takeItem(nextRow);

		ui.SubTrack_listWidget->insertItem(currentRow, itemTwo);
		ui.SubTrack_listWidget->insertItem(nextRow, itemOne);
	}

	QString mainpage = ui.MainTrack_listWidget->selectedItems()[0]->text();

	QList<QString> itemList;
	subOrder_.remove(mainpage);

	for (int i = 0; i < ui.SubTrack_listWidget->count(); i++)
	{
		itemList.append(ui.SubTrack_listWidget->item(i)->text());
	}

	subOrder_.insert(mainpage, itemList);
}

void OrderWindow::accept()
{
	for (int i = 0; i < ui.MainTrack_listWidget->count(); i++)
	{
		mainOrder_.append(ui.MainTrack_listWidget->item(i)->text());
	}

	logitech_->changeScreenOrder(mainOrder_, subOrder_);
}

void OrderWindow::reject()
{
	mainOrder_.clear();
	subOrder_.clear();

	hide();
}

QList<QString> OrderWindow::getMainOrder()
{
	return mainOrder_;
}

QMap<QString, QList<QString>> OrderWindow::getSubOrder()
{
	return subOrder_;
}