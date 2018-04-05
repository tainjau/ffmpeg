#include "xplay.h"
#include <QFileDialog.h>	//QT���ļ�������
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
		this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
	
	if (name.isEmpty())//���û��ѡ���ļ�
		return;

	this->setWindowTitle(name);//���ڱ���Ϊ����ѡ����ļ�

	if(!XFFmpeg::Get()->Open(name.toLocal8Bit()))
	{
		QMessageBox::information(this,"Error","file open failed!");
	}
}

Xplay::~Xplay()
{

}
