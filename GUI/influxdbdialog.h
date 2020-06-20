#ifndef INFLUXDBDIALOG_H
#define INFLUXDBDIALOG_H

#include <QDialog>
#include <HwaSettings.h>
#include <Defines.h>

namespace Ui {
class InfluxDbDialog;
}

class InfluxDbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfluxDbDialog(QWidget *parent = nullptr);
    ~InfluxDbDialog();

private:
    Ui::InfluxDbDialog *ui;

private slots:
    void accept();
};

#endif // INFLUXDBDIALOG_H
