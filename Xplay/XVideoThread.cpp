#include "XVideoThread.h"
#include "XFFmpeg.h"

bool isexit = false;

void XVideoThread::run()
{
	while (!isexit)
	{
		AVPacket pkt = XFFmpeg::Get()->Read(); //1����ȡ��Ƶ֡ 
		if (pkt.size <= 0)
		{
			msleep(10);	//�ͷ���Դ
			continue;
		}
		if (pkt.stream_index != XFFmpeg::Get()->videoStream)//�������Ƶ�������ȶ���
		{
			av_packet_unref(&pkt);//�ͷſռ�
			continue;
		}

		XFFmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);//�ͷſռ�
		if(XFFmpeg::Get()->fps > 0)
			msleep(1000/XFFmpeg::Get()->fps);//ÿһ֡�ĺ�����
	}

}
XVideoThread::XVideoThread()
{

}


XVideoThread::~XVideoThread()
{

}
