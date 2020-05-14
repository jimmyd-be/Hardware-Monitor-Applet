#include "CustomizePage.h"


CustomizePage::CustomizePage(KeyboardTypes type, LineEditPage * page, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), linePage_(page), lcdType_(type)
{
	initWindow();
}

CustomizePage::CustomizePage(KeyboardTypes type, LineEditPage * page, QList<CustomSettings> settings, QWidget *parent)
	: QWizardPage(parent), widget_(nullptr), layout_(nullptr), linePage_(page), tempSettings_(settings), lcdType_(type)
{
	initWindow();
}

CustomizePage::~CustomizePage()
{
	if (widget_ == nullptr)
	{
		delete widget_;
		widget_ = nullptr;
	}

	if (layout_ == nullptr)
	{
		delete layout_;
		layout_ = nullptr;
	}

	for (QWidget * widget : widgetList_)
	{
		ui.verticalLayout->removeWidget(widget);
	}

	widgetList_.clear();
}

void CustomizePage::initWindow()
{
	setTitle(tr("Introduction"));

	widget_ = new QWidget();

	ui.setupUi(widget_);

	layout_ = new QVBoxLayout;
	layout_->addWidget(widget_);
	setLayout(layout_);

	ui.Alligment_comboBox->setEnabled(false);
	ui.Font_pushButton->setEnabled(false);
	ui.FontColor_pushButton->setEnabled(false);
	ui.textScrolling->setEnabled(false);
	ui.LineSpace_spinBox->setEnabled(false);
	ui.lineSpacing_Label->setEnabled(false);

	connect(ui.GeneralSettings_checkBox, SIGNAL(toggled(bool)), this, SLOT(generalSettingsChanged()));
	connect(ui.Font_pushButton, SIGNAL(clicked()), this, SLOT(openFontDialog()));
	connect(ui.Alligment_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(alligmentChanged()));
	connect(ui.textScrolling, SIGNAL(stateChanged(int)), this, SLOT(textScrollingChanged()));
	connect(ui.LineSpace_spinBox, SIGNAL(valueChanged(int)), this, SLOT(lineSpaceChanged()));

	if (lcdType_ == KeyboardTypes::Color)
	{
		connect(ui.FontColor_pushButton, SIGNAL(clicked()), this, SLOT(openFontColorDialog()));
	}
	else
	{
		ui.FontColor_pushButton->hide();
	}
}

bool CustomizePage::validatePage()
{
	return true;
}

void CustomizePage::initializePage()
{
	for (QWidget * widget : widgetList_)
	{
		ui.verticalLayout->removeWidget(widget);
	}

	widgetList_.clear();

	QStringList list = optimizeLines(linePage_->getData());

	for (int i = 0; i < list.size(); i++)
	{
		CustomizePageLineWidget * widget = nullptr;

		if (tempSettings_.size() > i)
		{
			widget = new CustomizePageLineWidget(lcdType_, list[i], tempSettings_[i]);
		}
		else
		{
			widget = new CustomizePageLineWidget(lcdType_, list[i]);
		}

		ui.verticalLayout->addWidget(widget);

		widgetList_.append(widget);
	}

	if (widgetList_.size() > 0)
	{
		ui.Alligment_comboBox->setCurrentText(widgetList_[0]->getAlligment());
		ui.textScrolling->setChecked(widgetList_[0]->getTextScrolling());
		ui.LineSpace_spinBox->setEnabled(widgetList_[0]->getLineSpace());
	}
}

QStringList CustomizePage::optimizeLines(QStringList lineList)
{
	while (!lineList.isEmpty() && lineList.last().isEmpty())
	{
		lineList.removeLast();
	}

	return lineList;
}

int CustomizePage::nextId() const
{
	return -1;
}

QList<CustomSettings> CustomizePage::getData()
{
	QList<CustomSettings> data;

	for (CustomizePageLineWidget* widget : widgetList_)
	{
		data.append(widget->getSettings());
	}

	return data;
}

void CustomizePage::generalSettingsChanged()
{
	for (CustomizePageLineWidget* widget : widgetList_)
	{
		widget->setEnabled(!ui.GeneralSettings_checkBox->isChecked());
	}

	ui.Alligment_comboBox->setEnabled(ui.GeneralSettings_checkBox->isChecked());
	ui.Font_pushButton->setEnabled(ui.GeneralSettings_checkBox->isChecked());
	ui.FontColor_pushButton->setEnabled(ui.GeneralSettings_checkBox->isChecked());
	ui.textScrolling->setEnabled(ui.GeneralSettings_checkBox->isChecked());
	ui.LineSpace_spinBox->setEnabled(ui.GeneralSettings_checkBox->isChecked());
	ui.lineSpacing_Label->setEnabled(ui.GeneralSettings_checkBox->isChecked());
}

void CustomizePage::openFontDialog()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, widgetList_[0]->getFont());

	if (ok)
	{
		for (CustomizePageLineWidget* widget : widgetList_)
		{
			widget->setFont(font);
		}
	}
}

void CustomizePage::openFontColorDialog()
{
	QColorDialog dialog;
	QColor color;
	dialog.setCurrentColor(widgetList_[0]->getColor());

	color = dialog.getColor();

	for (CustomizePageLineWidget* widget : widgetList_)
	{
		widget->setColor(color);
	}
}

void CustomizePage::alligmentChanged()
{
	for (CustomizePageLineWidget* widget : widgetList_)
	{
		widget->setAlligment(ui.Alligment_comboBox->currentText());
	}
}

void CustomizePage::textScrollingChanged()
{
	for (CustomizePageLineWidget* widget : widgetList_)
	{
		widget->setTextScrolling(ui.textScrolling->isChecked());
	}
}

void CustomizePage::lineSpaceChanged()
{
	for (CustomizePageLineWidget* widget : widgetList_)
	{
		widget->setLineSpace(ui.LineSpace_spinBox->value());
	}
}