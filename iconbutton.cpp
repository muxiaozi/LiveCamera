#include "iconbutton.h"
#include <QMouseEvent>
#include <QDebug>

IconButton::IconButton(QWidget *parent) : QPushButton(parent)
{
	setFixedSize(32, 32);
	setIconSize(QSize(32, 32));
	setFlat(true);
}

void IconButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton){
		setIconSize(QSize(30, 30));
	}else{
		QPushButton::mousePressEvent(event);
	}
}

void IconButton::mouseReleaseEvent(QMouseEvent *event)
{
	setIconSize(QSize(32, 32));
	if(event->button() == Qt::LeftButton){
		if(rect().contains(event->pos()))
			emit clicked();
	}else{
		QPushButton::mouseReleaseEvent(event);
	}
}

//event->button()为什么不可用？
void IconButton::mouseMoveEvent(QMouseEvent *event)
{
	if(rect().contains(event->pos())){
		setIconSize(QSize(30, 30));
	}else{
		setIconSize(QSize(32, 32));
	}
}
