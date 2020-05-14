#pragma once

#include "localserver.h"

#include <QLocalSocket>

/**
 * @brief The Application class handles trivial application initialization procedures
 */
class SingleApplication: public QObject
{
	Q_OBJECT
public:
  SingleApplication();
  ~SingleApplication();
  bool isRunning();

  void sendMessage(QString);

signals:
  void messageReceivedSignal(QString);

private slots:
  void messageReceived(QString);
  
private:
  QLocalSocket* socket_;
  LocalServer* server_;
  bool isRunning_;

};

