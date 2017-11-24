#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class OneVideo;
class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	//创建菜单
	void createMenu();

	//创建内容
	void createContent();

	//重新布局
	void layoutChild();

private slots:
	//添加窗口
	void addWindowSlot();

	//删除窗口
	void removeWindowSlot();

	//关于
	void aboutSlot();

	//定时器
	void timerSlot();

	void childClosed(OneVideo *who);

private:
	//子窗口容器
	QList<OneVideo*> showList;

	//UI元素
	QWidget *mainContent;
	QPushButton *addBtn;

	//定时器
	QTimer *timer;
protected:
	void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
};

#endif // MAINWINDOW_H
