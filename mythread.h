#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QImage>

class MyThread : public QThread
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = NULL);
	explicit MyThread(QString ip, int port, QObject *parent = NULL);
	~MyThread();
	inline void setRunning(bool running);

signals:
	void transmitData(QImage image);
	void disconnectSlot();

protected:
	void run() Q_DECL_OVERRIDE;

private:
	QString ip;
	int port;
	volatile bool isRunning;
};

void MyThread::setRunning(bool running)
{
	this->isRunning = running;
}

#endif // MYTHREAD_H
