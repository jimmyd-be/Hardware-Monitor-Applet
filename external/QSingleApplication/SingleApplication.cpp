#include "SingleApplication.h"

/**
 * @brief SingleApplication::SingleApplication
 *  Constructor. Checks and fires up LocalServer or closes the program
 *  if another instance already exists
 */
SingleApplication::SingleApplication() : socket_(nullptr), server_(nullptr), isRunning_(false)
{
  socket_ = new QLocalSocket();

  // Attempt to connect to the LocalServer
  socket_->connectToServer("HWApplet");
 
  if(!socket_->waitForConnected(100))
  {
    // The attempt was insuccessful, so we continue the program
    server_ = new LocalServer();
    server_->start();
	QObject::connect(server_, SIGNAL(privateDataReceived(QString)), this, SLOT(messageReceived(QString)));
  }
  else
  {
	  isRunning_ = true;
  }
}

/**
 * @brief SingleApplication::~SingleApplication
 *  Destructor
 */
SingleApplication::~SingleApplication()
{
	
  if (server_ != nullptr)
  {
	  server_->terminate();
	  delete server_;
	  server_ = nullptr;
  }

  if (socket_ != nullptr)
  {
	  delete socket_;
	  socket_ = nullptr;
  }
}

/**
 * @brief SingleApplication::isRunning
 *  Weather the program should be terminated
 * @return bool
 */
bool SingleApplication::isRunning()
{
  return isRunning_;
}

/**
 * @brief SingleApplication::messageReceived
 *  Executed when the messageReceivedSignal command is sent to LocalServer
 */
void SingleApplication::messageReceived(QString message)
{
	if (message.contains("CMD:"))
	{
		message.replace(0, 4, "");
		emit messageReceivedSignal(message);
	}
}


void SingleApplication::sendMessage(QString message)
{
	socket_->connectToServer("HWApplet");

	if (socket_->waitForConnected(100))
	{
		message = "CMD:" + message;
		socket_->write(message.toUtf8().constData());
		socket_->flush();
		QThread::msleep(100);
		socket_->close();
	}
}
