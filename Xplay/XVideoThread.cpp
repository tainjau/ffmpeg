#include "XVideoThread.h"
#include "XFFmpeg.h"

bool isexit = false;

void XVideoThread::run()
{
	while (!isexit)
	{
		AVPacket pkt = XFFmpeg::Get()->Read(); //1、读取视频帧 
		if (pkt.size <= 0)
		{
			msleep(10);	//释放资源
			continue;
		}
		if (pkt.stream_index != XFFmpeg::Get()->videoStream)//如果是音频流，就先丢弃
		{
			av_packet_unref(&pkt);//释放空间
			continue;
		}

		XFFmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);//释放空间
		if(XFFmpeg::Get()->fps > 0)
			msleep(1000/XFFmpeg::Get()->fps);//每一帧的毫秒数
	}

}
XVideoThread::XVideoThread()
{

}


XVideoThread::~XVideoThread()
{

}
