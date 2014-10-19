#include "DataDialog.h"


DataDialog::DataDialog(QWidget *parent, QVector<Screen *> screenList)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


DataDialog::~DataDialog()
{
}

void DataDialog::accept()
{
	
}

void DataDialog::reject()
{

}
