#include "AboutDialog.h"


AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.label_2->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui.label_2->setOpenExternalLinks(true);

	ui.label_3->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui.label_3->setOpenExternalLinks(true);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

AboutDialog::~AboutDialog()
{
}


void AboutDialog::accept()
{
	hide();
}

void AboutDialog::reject()
{
	hide();
}