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
	//char *rgb = new char[OUT_WIDTH*OUT_HEIGHT * 4];	//ͼ�������RGBA
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
	//		av_packet_unref(&pkt);	//���������Ƶ��ʽ�� ���ͷŵ�
	//		continue;
	//	}

	//	AVFrame *yuv = XFFmpeg::Get()->Decode(&pkt);	//������Ƶ
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
	//AVFormatContext *ic = NULL;		//�����Ƶ���������ļ���Ϣ
	//AVPacket pkt;					//��Ŷ�ȡ��Ƶ�����ݰ�
	//AVCodecContext *videoCtx = NULL;//����������������
	//SwsContext *cCtx = NULL;		//����ת����������

	//int err;  
	//int got_picture = 0;		//����Ƶ�����ϰ汾����avcodec_decode_video2�У�����Ĳ��������������ȡ����Ƶ�᷵��1
	//int videoStream = 0;		//��¼��Ƶ�������streams[n]������ĵڼ�����
	//int outwidth = OUT_WIDTH;			//����Ŀ��
	//int outheight = OUT_HEIGHT;			//����ĸ߶�

	//char *rgb = new char[outwidth*outheight * 4];	//ͼ�������RGBA
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

	//totalSec = ic->duration / AV_TIME_BASE;		//�����������ʱ��
	//printf("file totalSec is %d\n", totalSec);
	//
	//for (int i = 0; i < ic->nb_streams;i++)
	//{
	//	AVCodecContext *enc = ic->streams[i]->codec;
	//			
	//	if (enc->codec_type == AVMEDIA_TYPE_VIDEO)//��ʾΪһ����Ƶ
	//	{
	//		videoStream = i;
	//		videoCtx = enc;
	//		AVCodec *codec = avcodec_find_decoder(enc->codec_id); //�ж�ϵͳ��û�����������

	//		if (!codec)
	//		{
	//			printf("video code not find!!\n");
	//			return -1;
	//		}
	//		err = avcodec_open2(enc, codec,NULL);	//�ҵ�ϵͳ������������Ļ����ʹ������������
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
	//AVFrame *yuv = av_frame_alloc();		//�������Ƶ֡

	//for (;;)			//����
	//{
	//	re = av_read_frame(ic, &pkt);
	//	if (re != 0) break;
	//	if (pkt.stream_index != videoStream)
	//	{
	//		av_packet_unref(&pkt);	//���������Ƶ��ʽ�� ���ͷŵ�
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

	//	//��ת����
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

	//	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };	//ת���Ŀ������
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
	//	av_packet_unref(&pkt);	//��������ռ䣬��ֹ�ڴ�й¶��
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
