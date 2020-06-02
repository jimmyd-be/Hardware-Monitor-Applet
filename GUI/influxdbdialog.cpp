#include "influxdbdialog.h"
#include "ui_influxdbdialog.h"

InfluxDbDialog::InfluxDbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfluxDbDialog)
{
    ui->setupUi(this);

    InfluxDbSettings settings = Settings::getInstance()->getInfluxSettings();

    ui->port->setValue(settings.port);
    ui->username->setText(settings.username);
    ui->password->setText(settings.password);
    ui->hostname->setText(settings.hostname);
}

InfluxDbDialog::~InfluxDbDialog()
{
    delete ui;
}

void InfluxDbDialog::accept()
{
    //TODO validate input

    InfluxDbSettings settings;

    settings.port = ui->port->value();
    settings.username = ui->username->text();
    settings.password = ui->password->text();
    settings.hostname = ui->hostname->text();

    Settings::getInstance()->setInfluxSettings(settings);

    this->close();
}
