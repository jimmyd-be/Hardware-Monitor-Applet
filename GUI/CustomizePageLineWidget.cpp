#include "CustomizePageLineWidget.h"


CustomizePageLineWidget::CustomizePageLineWidget(KeyboardTypes type, QString text, QWidget *parent)
	: QWidget(parent), color_(Qt::white)
{
	ui.setupUi(this);

	ui.text_label->setText(text);

	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);

	ui.FontColor_label->setAutoFillBackground(true);
	ui.FontColor_label->setPalette(palette_);

	connect(ui.Font_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));

	if (type == KeyboardTypes::Color)
	{
		connect(ui.FontColor_pushButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));
	}
	else
	{
		ui.FontColor_pushButton->hide();
	}
}

CustomizePageLineWidget::CustomizePageLineWidget(KeyboardTypes type, QString text, CustomSettings custom, QWidget *parent)
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
	
	if (type == KeyboardTypes::Color)
	{
		connect(ui.FontColor_pushButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));
	}
	else
	{
		ui.FontColor_pushButton->hide();
	}
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

void CustomizePageLineWidget::setEnabled(bool enabled)
{
	ui.Alligment_comboBox->setEnabled(enabled);
	ui.Font_pushButton->setEnabled(enabled);
	ui.FontColor_pushButton->setEnabled(enabled);
	ui.textScrolling->setEnabled(enabled);
	ui.LineSpace_spinBox->setEnabled(enabled);
	ui.text_label->setEnabled(enabled);
	ui.lineSpacing_label->setEnabled(enabled);
}

void CustomizePageLineWidget::setFont(QFont font)
{
	font_ = font;
}

void CustomizePageLineWidget::setColor(QColor color)
{
	color_= color;
}

QColor CustomizePageLineWidget::getColor()
{
	return color_;
}

QFont CustomizePageLineWidget::getFont()
{
	return font_;
}

void CustomizePageLineWidget::setAlligment(QString text)
{
	ui.Alligment_comboBox->setCurrentText(text);
}

QString CustomizePageLineWidget::getAlligment()
{
	return ui.Alligment_comboBox->currentText();
}

void CustomizePageLineWidget::setTextScrolling(bool textScolling)
{
	ui.textScrolling->setChecked(textScolling);
}

void CustomizePageLineWidget::setLineSpace(int lineSpace)
{
	ui.LineSpace_spinBox->setValue(lineSpace);
}

bool CustomizePageLineWidget::getTextScrolling()
{
	return ui.textScrolling->isChecked();
}

int CustomizePageLineWidget::getLineSpace()
{
	return ui.LineSpace_spinBox->value();
}
