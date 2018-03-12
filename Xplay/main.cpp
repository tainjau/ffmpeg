#include "xplay.h"
#include <QtWidgets/QApplication>
#include "XFFmpeg.h"

//static double r2d(AVRational r)
//{
//	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
//}

#define OUT_WIDTH	800
#define OUT_HEIGHT	600

int main(int argc, char *argv[])
{
	//char *rgb = new char[OUT_WIDTH*OUT_HEIGHT * 4];	//图像的数据RGBA
	//
	//if (XFFmpeg::Get()->Open("my.mp4"))
	//{
	//	printf("open success!\n");
	//}
	//else
	//{
	//	printf("open failed!%s", XFFmpeg::Get()->GetError().c_str());
	//	getchar();
	//	return -1;
	//}
	//
	//while (1)
	//{
	//	AVPacket pkt = XFFmpeg::Get()->Read();
	//	if (pkt.size == 0)
	//		break;
	//	printf("pts=%lld\n", pkt.pts);

	//	if (pkt.stream_index != XFFmpeg::Get()->videoStream)
	//	{
	//		av_packet_unref(&pkt);	//如果不是视频格式的 就释放掉
	//		continue;
	//	}

	//	AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);	//解码视频
	//	if (yuv)
	//	{
	//		printf("[D]");
	//		XFFmpeg::Get()->ToRGB(yuv, rgb, OUT_WIDTH, OUT_HEIGHT);
	//	}

	//	av_packet_unref(&pkt);
	//}


	//int totalSec = 0;
	//int pts = 0; 
	//char re = 0;

	//av_register_all();

	//char *path = "my.mp4"; 
	//AVFormatContext *ic = NULL;		//存放视频（流）的文件信息
	//AVPacket pkt;					//存放读取视频的数据包
	//AVCodecContext *videoCtx = NULL;//创建解码器的容器
	//SwsContext *cCtx = NULL;		//创建转码器的容器

	//int err;  
	//int got_picture = 0;		//在视频解码老版本函数avcodec_decode_video2中，传入的参数，如果函数获取到视频会返回1
	//int videoStream = 0;		//记录视频流存放在streams[n]数组里的第几个。
	//int outwidth = OUT_WIDTH;			//输出的宽度
	//int outheight = OUT_HEIGHT;			//输出的高度

	//char *rgb = new char[outwidth*outheight * 4];	//图像的数据RGBA
	//

	//re = avformat_open_input(&ic, path, 0, 0);

	//if (re != 0)
	//{
	//	char buf[1024] = { 0 };

	//	av_strerror(re, buf, sizeof(buf));

	//	printf("open failed %s\n",path, buf);
	//	getchar();
	//	return -1;
	//}

	//totalSec = ic->duration / AV_TIME_BASE;		//计算出进度条时间
	//printf("file totalSec is %d\n", totalSec);
	//
	//for (int i = 0; i < ic->nb_streams;i++)
	//{
	//	AVCodecContext *enc = ic->streams[i]->codec;
	//			
	//	if (enc->codec_type == AVMEDIA_TYPE_VIDEO)//表示为一个视频
	//	{
	//		videoStream = i;
	//		videoCtx = enc;
	//		AVCodec *codec = avcodec_find_decoder(enc->codec_id); //判断系统有没有这个解码器

	//		if (!codec)
	//		{
	//			printf("video code not find!!\n");
	//			return -1;
	//		}
	//		err = avcodec_open2(enc, codec,NULL);	//找到系统中这个解码器的话，就打开这个解码器。
	//		if (err != 0)
	//		{
	//			char buf[1024] = { 0 };
	//			av_strerror(re, buf, sizeof(buf));
	//			printf("buf\n", path, buf);
	//			return -2;
	//		}
	//		printf("open avcodec_open2 success!!!\n");
	//	}
	//}
	//
	//AVFrame *yuv = av_frame_alloc();		//分配的视频帧

	//for (;;)			//解码
	//{
	//	re = av_read_frame(ic, &pkt);
	//	if (re != 0) break;
	//	if (pkt.stream_index != videoStream)
	//	{
	//		av_packet_unref(&pkt);	//如果不是视频格式的 就释放掉
	//		continue;
	//	}

	//	pts = pkt.pts * r2d(ic->streams[pkt.stream_index]->time_base) *1000;
	//	
	//	re = avcodec_send_packet(videoCtx, &pkt);
	//	if (re != 0)
	//	{
	//		av_packet_unref(&pkt);
	//		continue;
	//	}
	//	re = avcodec_receive_frame(videoCtx, yuv);
	//	if (re != 0)
	//	{
	//		av_packet_unref(&pkt);
	//		continue;
	//	}
	//	printf("[D]");

	//	//打开转码器
	//	cCtx = sws_getCachedContext(cCtx, videoCtx->width,
	//		videoCtx->height,
	//		videoCtx->pix_fmt,
	//		outwidth, outheight,
	//		AV_PIX_FMT_BGRA,
	//		SWS_BICUBIC,
	//		NULL, NULL, NULL);
	//	
	//	if (!cCtx)
	//	{
	//		printf("sws_getCachedContext failed!!\n");
	//		break;
	//	}

	//	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };	//转码的目标数据
	//	data[0] = (uint8_t *)rgb;
	//	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	//	linesize[0] = outwidth * 4;

	//	int h = sws_scale(cCtx,yuv->data,yuv->linesize,0,videoCtx->height,
	//		data,
	//		linesize);

	//	if (h > 0)
	//		printf("(%d)", h);


	//	//re = avcodec_decode_video2(videoCtx, yuv, &got_picture, &pkt);
	//	//if (got_picture)
	//	//{
	//	//	printf("%d\n",re);
	//	//}

	//	printf("pts = %d\n", pts);
	//	av_packet_unref(&pkt);	//用于清理空间，防止内存泄露。
	//}
	//
	//if (cCtx)
	//{
	//	sws_freeContext(cCtx);
	//}


	//avformat_close_input(&ic);
	
	QApplication a(argc, argv);
	Xplay w;
	w.show();
	return a.exec();
}
