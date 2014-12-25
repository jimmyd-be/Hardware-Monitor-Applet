#include "SortScreenDialog.h"


SortScreenDialog::SortScreenDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


SortScreenDialog::~SortScreenDialog()
{
}

void SortScreenDialog::accept()
{
	
}

void SortScreenDialog::reject()
{
	
}
