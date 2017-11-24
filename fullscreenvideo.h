#ifndef FULLSCREENVIDEO_H
#define FULLSCREENVIDEO_H

#include <QDialog>
#include <QImage>

class FullScreenVideo : public QDialog
{
	Q_OBJECT
public:
	explicit FullScreenVideo(QWidget *parent = 0);

public slots:
	void updateImage(QImage image);

	// QWidget interface
protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
	QImage centralImage;
};

#endif // FULLSCREENVIDEO_H
