#include "GraphPageLineWidget.h"

GraphPageLineWidget::GraphPageLineWidget(QString symbol, Query query, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

    query_ = query;

	Id_label->hide();
	Symbol_label->hide();
	System_label->hide();

	Label_lineEdit->setText(symbol);

	Id_label->setText(query.identifier);
	Symbol_label->setText(symbol);
	System_label->setText(Defines::translateMonitorSystemEnum(query.system));
	Name_label->setText(query.name);
	Value_label->setText(Defines::translateQueryValueEnum(query.value));

	QColor color(randInt(0, 255), randInt(0, 255), randInt(0, 255));
	color_ = color;

	palette_.setColor(QPalette::Window, color);
	palette_.setColor(QPalette::WindowText, color);

	Color_label->setAutoFillBackground(true);
	Color_label->setPalette(palette_);

	connect(Color_pushButton, SIGNAL(clicked()), this, SLOT(openColorPicker()));
}

GraphPageLineWidget::GraphPageLineWidget(GraphLine line, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	Id_label->hide();
	Symbol_label->hide();
	System_label->hide();

	Label_lineEdit->setText(line.text);

	Id_label->setText(line.query.identifier);
	Symbol_label->setText(line.text);
	System_label->setText(Defines::translateMonitorSystemEnum(line.query.system));
	Name_label->setText(line.query.name);
	Value_label->setText(Defines::translateQueryValueEnum(line.query.value));

	color_ = line.color;

	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);

	Color_label->setAutoFillBackground(true);
	Color_label->setPalette(palette_);

	connect(Color_pushButton, SIGNAL(clicked()), this, SLOT(openColorPicker()));
}

GraphPageLineWidget::~GraphPageLineWidget()
{
	
}

void GraphPageLineWidget::openColorPicker()
{
	QColorDialog dialog;
	dialog.setCurrentColor(color_);

	color_ = dialog.getColor();

	palette_.setColor(QPalette::Window, color_);
	palette_.setColor(QPalette::WindowText, color_);
	Color_label->setPalette(palette_);
}

int GraphPageLineWidget::randInt(int low, int high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}

QPair<QString, Query> GraphPageLineWidget::getValue()
{
	QPair<QString, Query> pair;
	
    /*Query query;
	query.identifier = Id_label->text();
	query.system = Defines::translateMonitorSystemEnum(System_label->text());
	query.name = Name_label->text();
	query.value = Defines::translateQueryValueEnum(Value_label->text());
    query.precision = 0;*/

	pair.first = Label_lineEdit->text();
    pair.second = query_;

	return pair;
}

QColor GraphPageLineWidget::getColor()
{
	return color_;
}
