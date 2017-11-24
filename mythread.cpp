#include "mythread.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QImage>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
}

MyThread::MyThread(QString ip, int port, QObject *parent) : QThread(parent)
{
	this->ip = ip;
	this->port = port;
}

MyThread::~MyThread()
{
}

void MyThread::run()
{
	isRunning = true;

	QTcpSocket socket;
	connect(&socket, SIGNAL(disconnected()), this, SIGNAL(disconnectSlot()));
	socket.connectToHost(ip, port);
//	socket.connectToHost("192.168.47.131", 10086);
	if(!socket.waitForConnected(3000)){
		qDebug()<<"连接失败："<<socket.errorString();
		emit disconnectSlot();
		return;
	}else{
		qDebug()<<"连接成功！";
	}

	//发送HTTP请求
	socket.write("\r\n\r\n");
	if(socket.waitForBytesWritten(3000)){
		qDebug()<<"发送Http Request成功！";
	}else{
		qDebug()<<"发送Http Request失败！";
		return;
	}

	//读取响应
	QByteArray dataStream;
	QRegExp rx("\\d+");
	while(isRunning){
		if(socket.waitForReadyRead()){
			dataStream = socket.readLine();
			if(dataStream.contains("Content-Length")){
				int pos = rx.indexIn(dataStream);
				if(pos > -1){
					pos = rx.cap(0).toInt();
					dataStream.resize(pos);
					socket.readLine();
					socket.read(dataStream.data(), pos);
					emit transmitData(QImage::fromData(dataStream, "JPEG"));
				}

			}
		}
	}
}
