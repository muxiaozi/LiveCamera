#include "fullscreenvideo.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

FullScreenVideo::FullScreenVideo(QWidget *parent) : QDialog(parent)
{
	showFullScreen();
}

void FullScreenVideo::updateImage(QImage image)
{
	centralImage = image;
	update();
}

void FullScreenVideo::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter p(this);
	qreal rate = (qreal)height() / centralImage.height();
	int imageWidth = centralImage.width() * rate;
	p.drawImage(QRect((qreal)width() / 2 - (qreal)imageWidth /  2, 0, imageWidth, height()), centralImage);
}



