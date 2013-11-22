#include "tabwidget.h"
#include "ui_tabwidget.h"
#include "mainwindow.h"

TabWidget::TabWidget(WMI* wmi, MainWindow *mainWindow, QWidget *parent) :
	wmi_(wmi), QWidget(parent),
	ui(new Ui::TabWidget)
{
	ui->setupUi(this);

	connect(ui->removePageButton, SIGNAL(clicked()), mainWindow, SLOT(removePage()));
	connect(ui->addLineButton, SIGNAL(clicked()), this, SLOT(addLine()));
	connect(ui->browseButton, SIGNAL(clicked()), this, SLOT(browseBackground()));

	ui->browseLine->setDisabled(true);
}

TabWidget::~TabWidget()
{
	delete ui;
}

void TabWidget::addLine()
{
	QLayout* layout = this->layout();

	LineWidget* lineWidget = new LineWidget(wmi_, this, layout->count()-2+1);
	layout->addWidget(lineWidget);

	lineWidgets.append(lineWidget);
	layout->removeItem(ui->verticalSpacer);
	layout->addItem(ui->verticalSpacer);
}

void TabWidget::removeLine(LineWidget *line)
{
	QLayout* layout = this->layout();
	layout->removeWidget(line);

	int lineIndex = lineWidgets.indexOf(line);

	lineWidgets.removeOne(line);
	delete line;

	for(int i = lineIndex; i < lineWidgets.size(); i++)
	{
		lineWidgets[i]->setId(i+1);
	}
}

void TabWidget::disableBrowse(bool disable)
{
	ui->browseButton->setDisabled(disable);
}

QString TabWidget::getbackground()
{
	return ui->browseLine->text();
}

QVector<QString> TabWidget::getLines()
{
	 QVector<QString> list;

	for(int i = 0; i < lineWidgets.size(); i++)
	{
		list.push_back(lineWidgets[i]->getText());
	}

	return list;
}

void TabWidget::browseBackground()
{
	QFileDialog dialog;
	QStringList	selectedFiles;

	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter("Images (*.png *.jpg)");
	dialog.setOption(QFileDialog::DontUseNativeDialog);

	if (dialog.exec())
	{
		selectedFiles = dialog.selectedFiles();

		QImage image(selectedFiles.at(0));

		if(image.height() != 240 && image.width() != 320)
		{
			QMessageBox messageBox;
			messageBox.setText("File is not an image or the dimension is not 320x240");
			messageBox.exec();
		}

		else
		{
			 ui->browseLine->setText(selectedFiles.at(0));
		}
	}	

}