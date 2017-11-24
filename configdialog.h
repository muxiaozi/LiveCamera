#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

namespace Ui {
	class ConfigDialog;
}

class ConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

	QString getIP() const;
	int getPort() const;

private:
	Ui::ConfigDialog *ui;

public slots:
	void accept() Q_DECL_OVERRIDE;

};

#endif // CONFIGDIALOG_H
