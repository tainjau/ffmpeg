#include "VideoWidget.h"
#include <QPainter>
#include "XFFmpeg.h"
#include "XVideoThread.h"
VideoWidget::VideoWidget(QWidget *p) :QOpenGLWidget(p)
{
	//XFFmpeg::Get()->Open("my.mp4");
	startTimer(20);
	XVideoThread::Get()->start();	//	�����߳�
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
	static QImage *image = NULL;
	if (image == NULL)
	{
		uchar *buf = new uchar[width()*height() * 4];
		image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
	}

	//AVPacket pkt = XFFmpeg::Get()->Read();		//1����ȡ��Ƶ֡
	//if (pkt.stream_index != XFFmpeg::Get()->videoStream)
	//{
	//	av_packet_unref(&pkt);		//���������Ƶ��ʽ�� ���ͷŵ�
	//	return;
	//}

	//if (pkt.size == 0) return;
	//AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);	//2������
	//av_packet_unref(&pkt);							//������ͷŵ�֡����
	//if (yuv == NULL) return;
	
	XFFmpeg::Get()->ToRGB((char*)image->bits(), width(), height());	//3��ת��
																			//image->bits()��image�Ĵ洢�ռ�

	QPainter painter;
	painter.begin(this);	//��������Ļ

	painter.drawImage(QPoint(0, 0),*image);

	painter.end();
}
void VideoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}