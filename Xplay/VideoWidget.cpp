#include "VideoWidget.h"
#include <QPainter>
#include "XFFmpeg.h"
#include "XVideoThread.h"
VideoWidget::VideoWidget(QWidget *p) :QOpenGLWidget(p)
{
	//XFFmpeg::Get()->Open("my.mp4");
	startTimer(20);
	XVideoThread::Get()->start();	//	启动线程
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

	//AVPacket pkt = XFFmpeg::Get()->Read();		//1、读取视频帧
	//if (pkt.stream_index != XFFmpeg::Get()->videoStream)
	//{
	//	av_packet_unref(&pkt);		//如果不是视频格式的 就释放掉
	//	return;
	//}

	//if (pkt.size == 0) return;
	//AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);	//2、解码
	//av_packet_unref(&pkt);							//解码后释放掉帧数据
	//if (yuv == NULL) return;
	
	XFFmpeg::Get()->ToRGB((char*)image->bits(), width(), height());	//3、转码
																			//image->bits()是image的存储空间

	QPainter painter;
	painter.begin(this);	//先清理屏幕

	painter.drawImage(QPoint(0, 0),*image);

	painter.end();
}
void VideoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}