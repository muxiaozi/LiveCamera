#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConfigDialog)
{
	ui->setupUi(this);
	ui->lblIP->clear();
	ui->lblPort->clear();
}

ConfigDialog::~ConfigDialog()
{
	delete ui;
}

QString ConfigDialog::getIP() const
{
	return ui->txtIP->text();
}

int ConfigDialog::getPort() const
{
	return ui->txtPort->text().toInt();
}

void ConfigDialog::accept()
{
	ui->lblIP->clear();
	ui->lblPort->clear();

	if(ui->txtIP->text().isEmpty()){
		ui->lblIP->setText("IP地址不能为空");
		return;
	}

	if(ui->txtPort->text().isEmpty()){
		ui->lblPort->setText("端口号不能为空");
		return;
	}

	QDialog::accept();
}
