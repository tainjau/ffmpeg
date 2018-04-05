#include "XFFmpeg.h"
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")

//Ϊ�˽�pkt.ptsת������ĺ�����
static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

int XFFmpeg::Open(const char *path)
{
	int re = 0;
	int err = 0;

	Close();
	mutex.lock();
	re = avformat_open_input(&ic, path, 0, 0);		//��
	if (re != 0)
	{
		mutex.unlock();
		av_strerror(re, errorbuf, sizeof(errorbuf));
		printf("open failed %s\n", path, errorbuf);		
		return 0;
	}
	totalMs = (ic->duration / AV_TIME_BASE)*1000;

	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVCodecContext *enc = ic->streams[i]->codec;
				
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)//��ʾΪһ����Ƶ
		{
			videoStream = i;
			fps = r2d(ic->streams[i]->avg_frame_rate);		//��ȡfps
			AVCodec *codec = avcodec_find_decoder(enc->codec_id); //�ж�ϵͳ��û�����������
			if (!codec)
			{
				mutex.unlock();
				printf("video code not find!!\n");
				return 0;
			}

			err = avcodec_open2(enc, codec,NULL);	//�ҵ�ϵͳ������������Ļ����ʹ������������
			if (err != 0)
			{
				mutex.unlock();
				char buf[1024] = { 0 };
				av_strerror(re, errorbuf, sizeof(errorbuf));
				printf("buf\n", path, errorbuf);
				return 0;
			}
			printf("open avcodec_open2 success!!!\n");
		}
	}

	mutex.unlock();
	return totalMs;
}

AVPacket XFFmpeg::Read()
{
	AVPacket pkt;
	int err = 0;
	memset(&pkt,0,sizeof(AVPacket));
	mutex.lock();

	if (!ic)	//�ж���Ƶ�ļ�����û��û���򿪵Ļ���ֱ���˳���
	{
		mutex.unlock();
		return pkt;	//��ʱ���pktҲ�ǿյ�
	}

	err = av_read_frame(ic, &pkt);
	if (err != 0)
	{
		mutex.unlock();
		av_strerror(err, errorbuf, sizeof(errorbuf));
	}
	mutex.unlock();
	return pkt;
}

void XFFmpeg::Close()
{
	mutex.lock();
	if (ic)	avformat_close_input(&ic);
	if (yuv) av_frame_free(&yuv);
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = NULL;
	}

	mutex.unlock();
}
std::string XFFmpeg::GetError()
{
	mutex.lock();
	std::string re = this->errorbuf;
	mutex.unlock();
	return re;
}

AVFrame *XFFmpeg::Decode(const AVPacket *pkt)
{
	int re = 0;
	mutex.lock();
	if (!ic)	//�ж���Ƶ�ļ�����û��û���򿪵Ļ���ֱ���˳���
	{
		mutex.unlock();
		return NULL;	//��ʱ���pktҲ�ǿյ�
	}

	if (yuv == NULL)
	{
		yuv = av_frame_alloc();
	}

	re = avcodec_send_packet(ic->streams[pkt->stream_index]->codec,pkt);
	if (re != 0)
	{
		mutex.unlock();
		//av_packet_unref(&pkt);
		return NULL;
	}
	re = avcodec_receive_frame(ic->streams[pkt->stream_index]->codec,yuv);
	if (re != 0)
	{
		mutex.unlock();
		//av_packet_unref(&pkt);
		return NULL;
	}

	mutex.unlock();
	pts = yuv->pts*r2d(ic->streams[pkt->stream_index]->time_base)*1000;//�õ���ǰ����ĺ�����
	return yuv;
}

bool XFFmpeg::Seek(float pos)
{
	mutex.lock();
	if (!ic)	//	�ж��Ƿ��
	{
		mutex.unlock();
		return false;
	}

	int64_t stamp = 0;
	stamp = pos *ic->streams[videoStream]->duration;//duration����Ƶ���ܳ��ȣ�����pos�õ��������϶�λ�ö�Ӧ����Ƶλ��
	int re = av_seek_frame(ic, videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);//��ǰ���Ҳ��ҵ��ؼ�֡
	avcodec_flush_buffers(ic->streams[videoStream]->codec);//��ջ�����

	mutex.unlock();
	if (re >= 0)
		return true;

	return false;
}

bool XFFmpeg::ToRGB(char *out, int outwidth, int outheight)
{
	mutex.lock();
	if (!ic || !yuv)	//�ж���Ƶ�ļ�����û��û���򿪵Ļ���ֱ���˳���
	{
		mutex.unlock();
		return false;	
	}
	AVCodecContext *videoCtx = ic->streams[this->videoStream]->codec;//��ic�е�streams�������ҵ����codec,
	//��ת����
	cCtx = sws_getCachedContext(cCtx, videoCtx->width,
		videoCtx->height,
		videoCtx->pix_fmt,
		outwidth, outheight,
		AV_PIX_FMT_BGRA,
		SWS_BICUBIC,
		NULL, NULL, NULL);
	
	if (!cCtx)
	{
		mutex.unlock();
		printf("sws_getCachedContext failed!!\n");
		return false;
	}

	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };	//ת���Ŀ������
	data[0] = (uint8_t *)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;

	int h = sws_scale(cCtx,yuv->data,yuv->linesize,0,videoCtx->height,
		data,
		linesize);

	if (h > 0)
		printf("(%d)", h);

	mutex.unlock();
	return true;
}

XFFmpeg::XFFmpeg()
{
	errorbuf[0] = '\0';
	av_register_all();		//ע�����еı���������ļ���ʽ��
}


XFFmpeg::~XFFmpeg()
{
}
