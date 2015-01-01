#include "CustomizePageLineWidget.h"


CustomizePageLineWidget::CustomizePageLineWidget(QString text, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.Line_lineEdit->setText(text);

	connect(ui.Font_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
}

CustomizePageLineWidget::~CustomizePageLineWidget()
{

}

CustomSettings CustomizePageLineWidget::getSettings()
{
	CustomSettings settings;
	settings.aligment = Defines::translateAligmentEnum(ui.Alligment_comboBox->currentText());
	settings.textScrolling = ui.textScrolling->isChecked();
	settings.font = font_;

	return settings;
}

void CustomizePageLineWidget::openFontDialog()
{	
	bool ok;
	font_ = QFontDialog::getFont(&ok);
}