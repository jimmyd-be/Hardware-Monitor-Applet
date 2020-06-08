#include "influxdb.h"
#include "../HwaSettings.h"

InfluxDb::InfluxDb(QObject * parent): QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readData(QNetworkReply*)));

}


InfluxDb::~InfluxDb()
{
  delete manager;
}


QVector<HardwareSensor> InfluxDb::getAllSensors()
{
    QVector<HardwareSensor> sensors;

    // curl -G 'http://localhost:8086/query?pretty=true' --data-urlencode "db=telegraf" --data-urlencode "q=show measurements"
    QNetworkRequest request(getUrl("show MEASUREMENTS"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply * reply = manager->get(request);

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect( manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(&QEventLoop::quit));
    connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
    timer.start(1000);
    loop.exec();

    QVector<QString> measurements = readMeasurements(reply);

    for(int i = 0; i < measurements.size(); i++)
    {
        HardwareSensor sensor;
        sensor.hardware = measurements[i];

        //TODO query for columns of the measurements
    }

    delete reply;
    return sensors;
}

QVector<QString> InfluxDb::readMeasurements(QNetworkReply* reply)
{
    QVector<QString> response;
    if(reply->error() == QNetworkReply::NoError)
    {
        QString response = reply->readAll();

        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject root = jsonResponse.object();

        QJsonObject results = root.value(QString("results")).toArray()[0].toObject();

        QJsonArray result = results.value(QString("series")).toArray()[0].toObject().value("values").toArray();

        for(int i = 0; i < result.size(); i++)
        {
            qDebug() << result[i].toArray()[0].toString();

            response.append(result[i].toArray()[0].toString());
        }
    }
    else // handle error
    {
      qDebug() << reply->errorString();
    }

  return response;
}

MonitorSystem InfluxDb::getMonitorSystem()
{
    return MonitorSystem::INFLUXDB;
}

HardwareSensor InfluxDb::getData(Query query)
{
    HardwareSensor sensor;
    return sensor;
}

QUrl InfluxDb::getUrl(QString query)
{
    InfluxDbSettings influxSettings = HwaSettings::getInstance()->getInfluxSettings();

    QString url = "http://" + influxSettings.hostname + ":" + QString::number(influxSettings.port) + "/query?db=" + influxSettings.database + "&q=" + QUrl::toPercentEncoding(query);

    if(!influxSettings.username.isEmpty() && !influxSettings.password.isEmpty())
    {
        url += "&u=" + influxSettings.username + "&p=" + influxSettings.password;
    }

    return QUrl(url);
}
