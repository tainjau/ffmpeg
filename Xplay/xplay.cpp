#include "xplay.h"
#include <QFileDialog.h>	//QT的文件窗口类
#include <QMessageBox>
#include "XFFmpeg.h"

Xplay::Xplay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void Xplay::open()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择视频文件"));
	
	if (name.isEmpty())//如果没有选择文件
		return;

	this->setWindowTitle(name);//窗口标题为我们选择的文件

	if(!XFFmpeg::Get()->Open(name.toLocal8Bit()))
	{
		QMessageBox::information(this,"Error","file open failed!");
	}
}

Xplay::~Xplay()
{

}
