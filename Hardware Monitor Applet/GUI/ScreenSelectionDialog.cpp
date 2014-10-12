#include "ScreenSelectionDialog.h"


ScreenSelectionDialog::ScreenSelectionDialog(QWidget *parent, QVector<Screen *> screenList)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


ScreenSelectionDialog::~ScreenSelectionDialog()
{
}

void ScreenSelectionDialog::accept()
{
	bool error = false;

	name_ = ui.screenText->text();

	if (ui.buttonGroup->checkedButton()->text() == "Normal Screen")
	{
		type_ = ScreenType::Normal;
	}
	else if (ui.buttonGroup->checkedButton()->text() == "Graph Screen")
	{
		type_ = ScreenType::Graph;
	}

	if (name_.isEmpty())
	{
		error = true;
		QMessageBox message;
		message.setText("There is no name entered.");
		message.exec();
	}
	else
	{
		for (Screen * screen : screenList_)
		{
			if (screen->getName() == name_)
			{
				error = true;
				QMessageBox message;
				message.setText("There is already a screen named " + name_);
				message.exec();
				break;
			}
		}
	}

	if (!error)
	{
		hide();
	}
}

void ScreenSelectionDialog::reject()
{
	name_ = "";
	type_ = ScreenType::No;

	hide();
}

QString ScreenSelectionDialog::getScreenName()
{
	return name_;
}

ScreenType ScreenSelectionDialog::getScreenType()
{
	return type_;
}