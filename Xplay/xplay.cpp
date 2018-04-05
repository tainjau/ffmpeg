#include "xplay.h"
#include <QFileDialog.h>	//QT���ļ�������
#include <QMessageBox>
#include "XFFmpeg.h"

static bool g_isPressSlider = false;

Xplay::Xplay(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	startTimer(40);	//������ʱ�� 40ms
}

void Xplay::timerEvent(QTimerEvent *e)
{
	char buf[1024] = { 0 };
	int min = (XFFmpeg::Get()->pts / 1000) / 60;
	int sec = (XFFmpeg::Get()->pts / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playtime->setText(buf);

	if (XFFmpeg::Get()->totalMs > 0)
	{	
		float rate = (float)XFFmpeg::Get()->pts / (float)XFFmpeg::Get()->totalMs;
		if (!g_isPressSlider)
			ui.playslider->setValue(rate * 1000);
	}

}

void Xplay::sliderPressed()//��������ѹ����
{
	g_isPressSlider = true;
}
void Xplay::sliderReleased()//�������ͷŴ���
{
	g_isPressSlider = false;
	float pos = 0;
	pos = (float)ui.playslider->value() / (float)(ui.playslider->maximum() + 1);

	XFFmpeg::Get()->Seek(pos);
}

void Xplay::open()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
	
	if (name.isEmpty())//���û��ѡ���ļ�
		return;

	this->setWindowTitle(name);//���ڱ���Ϊ����ѡ����ļ�
	int totalMs = XFFmpeg::Get()->Open(name.toLocal8Bit());
	if (totalMs <= 0)
	{
		QMessageBox::information(this,"Error","file open failed!");
		return;
	}
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf,"/%03d:%02d",min,sec);
	ui.totaltime->setText(buf);
}

Xplay::~Xplay()
{

}
