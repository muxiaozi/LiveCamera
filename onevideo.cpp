#include "onevideo.h"
#include "iconbutton.h"
#include "mythread.h"
#include "configdialog.h"
#include "fullscreenvideo.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>
#include <QLinearGradient>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QImage>
#include <QLabel>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

const int OneVideo::WIDTH = 320; //480
const int OneVideo::HEIGHT = 240; //320

OneVideo::OneVideo(QWidget *parent) : QFrame(parent),
	centralImage(":/images/icon.png")
{
	resize(WIDTH, HEIGHT);
	createToolButtons();
	createIpPortLabel();
	setFrameShape(QFrame::Box);
	setBackgroundRole(QPalette::Light);
	setAutoFillBackground(true);
	setMouseTracking(true);
	isPlay = false;
	cameraBtn->setEnabled(false);
	recordBtn->setEnabled(false);
	fullScreenBtn->setEnabled(false);
	networkThread = NULL;
}

OneVideo::~OneVideo()
{
	if(networkThread != NULL){
		networkThread->setRunning(false);
		networkThread->wait();
		networkThread->deleteLater();
		networkThread = NULL;
	}
}

void OneVideo::createToolButtons()
{
	closeBtn = new IconButton(this);
	closeBtn->setIcon(QIcon(":/images/close.png"));
	closeBtn->move(WIDTH - closeBtn->width() - 8, 8);
	connect(closeBtn, SIGNAL(clicked(bool)), SLOT(close()));
	connect(closeBtn, SIGNAL(clicked(bool)), SLOT(deleteLater()));

	QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
	buttonsLayout->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
	buttonsLayout->setSpacing(30);

	playBtn = new IconButton(this);
	playBtn->setIcon(QIcon(":/images/play.png"));
	buttonsLayout->addWidget(playBtn);
	connect(playBtn, SIGNAL(clicked(bool)), SLOT(playBtnSlot()));

	cameraBtn = new IconButton(this);
	cameraBtn->setIcon(QIcon(":/images/camera.png"));
	buttonsLayout->addWidget(cameraBtn);
	connect(cameraBtn, SIGNAL(clicked(bool)), SLOT(cameraBtnSlot()));

	recordBtn = new IconButton(this);
	recordBtn->setIcon(QIcon(":/images/record.png"));
	buttonsLayout->addWidget(recordBtn);
	connect(recordBtn, SIGNAL(clicked(bool)), SLOT(recordBtnSlot()));

	fullScreenBtn = new IconButton(this);
	fullScreenBtn->setIcon(QIcon(":/images/fullscreen.png"));
	buttonsLayout->addWidget(fullScreenBtn);
	connect(fullScreenBtn, SIGNAL(clicked(bool)), SLOT(fullScreenBtnSlot()));
}

void OneVideo::createIpPortLabel()
{
	ipPortLabel = new QLabel(this);
	ipPortLabel->setFont(QFont("Consolas", 10, 1));
	ipPortLabel->setMargin(10);
	ipPortLabel->resize(200, 50);
}

void OneVideo::playBtnSlot()
{
	ConfigDialog dialog(this);
	if(isPlay){
		isPlay = false;

		if(networkThread != NULL){
			networkThread->setRunning(false);
			networkThread->wait();
			networkThread->deleteLater();
			networkThread = NULL;
		}

		playBtn->setIcon(QIcon(":/images/play.png"));
		ipPortLabel->clear();
		cameraBtn->setEnabled(false);
		recordBtn->setEnabled(false);
		fullScreenBtn->setEnabled(false);
		centralImage.load(":/images/icon.png");
		update();
	}else{
		if(dialog.exec() == QDialog::Accepted){
			networkThread = new MyThread(dialog.getIP(), dialog.getPort());
			connect(networkThread, SIGNAL(disconnectSlot()), SLOT(disconnectSlot()));
			connect(networkThread, SIGNAL(transmitData(QImage)), SLOT(updateImage(QImage)));
			networkThread->start();

			playBtn->setIcon(QIcon(":/images/pause.png"));
			ipPortLabel->setText(QString("IP  : %1\nPORT: %2").arg(dialog.getIP()).arg(dialog.getPort()));
			cameraBtn->setEnabled(true);
			recordBtn->setEnabled(true);
			fullScreenBtn->setEnabled(true);

			isPlay = true;
		}
	}
}

void OneVideo::cameraBtnSlot()
{
	QFile file;
	QString fileName = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	centralImage.save(fileName + ".jpg", "JPEG");
}

void OneVideo::recordBtnSlot()
{
}

void OneVideo::fullScreenBtnSlot()
{
	//先取消发送消息到小窗口
	disconnect(networkThread, SIGNAL(transmitData(QImage)),
			   this, SLOT(updateImage(QImage)));

	//发送消息到全屏窗口
	FullScreenVideo fullScreenVideo(this);
	connect(networkThread, SIGNAL(transmitData(QImage)),
			&fullScreenVideo, SLOT(updateImage(QImage)));
	fullScreenVideo.exec();

	//恢复发送消息到小窗口
	connect(networkThread, SIGNAL(transmitData(QImage)),
			this, SLOT(updateImage(QImage)));
}

void OneVideo::updateImage(QImage image)
{
	if(isPlay){
		centralImage = image;
		update();
	}
}

void OneVideo::disconnectSlot()
{
	QMessageBox::warning(this, "连接失败", "请注意！\n您的连接已经断开！");
	if(networkThread != NULL){
		networkThread->setRunning(false);
		networkThread->wait();
		networkThread->deleteLater();
		networkThread = NULL;
	}
	playBtn->setIcon(QIcon(":/images/play.png"));
	ipPortLabel->clear();
	cameraBtn->setEnabled(false);
	recordBtn->setEnabled(false);
	fullScreenBtn->setEnabled(false);
	centralImage.load(":/images/icon.png");
	update();
	isPlay = false;
}

void OneVideo::closeEvent(QCloseEvent *event)
{
	QFrame::closeEvent(event);
	emit closeSignal(this);
}

void OneVideo::paintEvent(QPaintEvent *event)
{
	QFrame::paintEvent(event);
	QPainter p(this);
	p.drawImage(width() / 2 - centralImage.width() / 2,
				height() / 2 - centralImage.height() / 2,
				centralImage);
}

void OneVideo::mouseMoveEvent(QMouseEvent *event)
{
	if(event->y() > rect().bottom() - 50 || event->y() < 50){
		if(!isButtonsShow){
			isButtonsShow = true;
			closeBtn->show();
			playBtn->show();
			cameraBtn->show();
			recordBtn->show();
			fullScreenBtn->show();
		}
	}else{
		if(isButtonsShow){
			closeBtn->hide();
			playBtn->hide();
			cameraBtn->hide();
			recordBtn->hide();
			fullScreenBtn->hide();
			isButtonsShow = false;
		}
	}
}

void OneVideo::leaveEvent(QEvent *event)
{
	Q_UNUSED(event);
	if(isButtonsShow){
		closeBtn->hide();
		playBtn->hide();
		cameraBtn->hide();
		recordBtn->hide();
		fullScreenBtn->hide();
		isButtonsShow = false;
	}
}
