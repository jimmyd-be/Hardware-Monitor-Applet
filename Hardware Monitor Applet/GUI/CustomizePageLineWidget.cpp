#include "CustomizePageLineWidget.h"


CustomizePageLineWidget::CustomizePageLineWidget(QString text, QWidget *parent)
	: QWidget(parent), color_(Qt::white)
{
	ui.setupUi(this);

	ui.text_label->setText(text);

	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);

	ui.FontColor_label->setAutoFillBackground(true);
	ui.FontColor_label->setPalette(palette_);

	connect(ui.Font_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(ui.FontColor_pushButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));
}

CustomizePageLineWidget::CustomizePageLineWidget(QString text, CustomSettings custom, QWidget *parent)
	: QWidget(parent), color_(Qt::white)
{
	ui.setupUi(this);

	ui.text_label->setText(text);
	ui.LineSpace_spinBox->setValue(custom.lineSpacing);
	ui.Alligment_comboBox->setCurrentText(Defines::translateAligmentEnum(custom.aligment));
	ui.textScrolling->setChecked(custom.textScrolling);

	font_ = custom.font;
	color_ = custom.fontColor;
	
	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);

	ui.FontColor_label->setAutoFillBackground(true);
	ui.FontColor_label->setPalette(palette_);

	connect(ui.Font_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(ui.FontColor_pushButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));
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
	settings.fontColor = color_;
	settings.lineSpacing = ui.LineSpace_spinBox->value();

	return settings;
}

void CustomizePageLineWidget::openFontDialog()
{	
	bool ok;
	font_ = QFontDialog::getFont(&ok, font_);
}

void CustomizePageLineWidget::openFontColorDialog()
{
	QColorDialog dialog;
	dialog.setCurrentColor(color_);

	color_ = dialog.getColor();

	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);
	ui.FontColor_label->setPalette(palette_);
}