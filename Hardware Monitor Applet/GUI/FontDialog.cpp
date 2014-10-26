#include "FontDialog.h"


FontDialog::FontDialog(Screen * screenData, QWidget *parent)
	: QDialog(parent), screenData_(screenData)
{
	ui.setupUi(this);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.pickColorButton, SIGNAL(clicked()), this, SLOT(openColorPicker()));

	/*ui.colorLabel->setAutoFillBackground(true);
	QPalette pal = ui.colorLabel->palette();
	pal.setColor(QPalette::Window, screenData_->getFont().color);
	ui.colorLabel->setPalette(pal);*/
}


FontDialog::~FontDialog()
{
}

void FontDialog::accept()
{
	close();
}

void FontDialog::reject()
{
	close();
}

void FontDialog::closeEvent(QCloseEvent * event)
{
	reject();
}

void FontDialog::openColorPicker()
{
	QColorDialog dialog;

	//dialog.setCurrentColor(screenData_->getFont().color);

	dialog.exec();

	QColor color = dialog.selectedColor();

	ui.colorLabel->setAutoFillBackground(true);
	QPalette pal = ui.colorLabel->palette();
	pal.setColor(QPalette::Window, color);
	ui.colorLabel->setPalette(pal);
}