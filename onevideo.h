#ifndef ONEVIDEO_H
#define ONEVIDEO_H

#include <QFrame>
#include <QImage>

class IconButton;
class MyThread;
class QLabel;

class OneVideo : public QFrame
{
	Q_OBJECT
public:
	explicit OneVideo(QWidget *parent = 0);
	~OneVideo();
	void createToolButtons();
	void createIpPortLabel();

	static const int WIDTH;
	static const int HEIGHT;

private slots:
	void playBtnSlot();
	void cameraBtnSlot();
	void recordBtnSlot();
	void fullScreenBtnSlot();
	void updateImage(QImage image);
	void disconnectSlot();

signals:
	void closeSignal(OneVideo *who);

protected:
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
	IconButton *closeBtn;
	IconButton *playBtn;
	IconButton *cameraBtn;
	IconButton *recordBtn;
	IconButton *fullScreenBtn;
	QLabel *ipPortLabel;

	//显示的图像
	QImage centralImage;
	//按钮工具栏显示状态
	bool isButtonsShow;
	//是否正在运行
	bool isPlay;

	//网络线程
	MyThread *networkThread;

};

#endif // ONEVIDEO_H
