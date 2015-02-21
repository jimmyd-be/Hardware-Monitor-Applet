#include "localserver.h"

#include <QFile>
#include <QStringList>

/**
 * @brief LocalServer::LocalServer
 *  Constructor
 */
LocalServer::LocalServer() : server_(nullptr)
{
	server_ = new QLocalServer();
}

/**
 * @brief LocalServer::~LocalServer
 *  Destructor
 */
LocalServer::~LocalServer()
{
  server_->close();

  for (QLocalSocket* client: clients)
  {
	  client->close();
  }

}

/**
 * -----------------------
 * QThread requred methods
 * -----------------------
 */

/**
 * @brief run
 *  Initiate the thread.
 */
void LocalServer::run()
{
  QObject::connect(server_, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
  QObject::connect(this, SIGNAL(privateDataReceived(QString)), this, SLOT(slotOnData(QString)));

  QString serverName = "HWApplet";
  server_->listen(serverName);
  while(server_->isListening() == false)
  {
    server_->listen(serverName);
    msleep(100);
  }
  exec();
}

/**
 * @brief LocalServer::exec
 *  Keeps the thread alive. Waits for incomming connections
 */
void LocalServer::exec()
{
  while(server_->isListening())
  {
    msleep(100);
    server_->waitForNewConnection(100);
    for(int i = 0; i < clients.size(); ++i)
    {
      if(clients[i]->waitForReadyRead(100)){
        QByteArray data = clients[i]->readAll();
        emit privateDataReceived(data);
      }
    }
  }
}

/**
 * -------
 * SLOTS
 * -------
 */

/**
 * @brief LocalServer::slotNewConnection
 *  Executed when a new connection is available
 */
void LocalServer::slotNewConnection()
{
  clients.push_front(server_->nextPendingConnection());
}

/**
 * @brief LocalServer::slotOnData
 *  Executed when data is received
 * @param data
 */
void LocalServer::slotOnData(QString data)
{
  if(data.contains("CMD:", Qt::CaseInsensitive)){
	  onCMD(data);
  } else {
    emit dataReceived(data);
  }
}

/**
 * -------
 * Helper methods
 * -------
 */

void LocalServer::onCMD(QString data)
{
  if (data.contains("CMD:"))
  {
	  data.replace(0, 4, "");
	  emit messageReceivedSignal(data);
  }
}
