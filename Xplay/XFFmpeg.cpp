#include "XFFmpeg.h"
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")

//为了将pkt.pts转换成秒的函数。
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
	re = avformat_open_input(&ic, path, 0, 0);		//打开
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
				
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)//表示为一个视频
		{
			videoStream = i;
			fps = r2d(ic->streams[i]->avg_frame_rate);		//获取fps
			AVCodec *codec = avcodec_find_decoder(enc->codec_id); //判断系统有没有这个解码器
			if (!codec)
			{
				mutex.unlock();
				printf("video code not find!!\n");
				return 0;
			}

			err = avcodec_open2(enc, codec,NULL);	//找到系统中这个解码器的话，就打开这个解码器。
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

	if (!ic)	//判断视频文件被打开没，没被打开的话，直接退出。
	{
		mutex.unlock();
		return pkt;	//这时候的pkt也是空的
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
	if (!ic)	//判断视频文件被打开没，没被打开的话，直接退出。
	{
		mutex.unlock();
		return NULL;	//这时候的pkt也是空的
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
	pts = yuv->pts*r2d(ic->streams[pkt->stream_index]->time_base)*1000;//得到当前画面的毫秒数
	return yuv;
}

bool XFFmpeg::Seek(float pos)
{
	mutex.lock();
	if (!ic)	//	判断是否打开
	{
		mutex.unlock();
		return false;
	}

	int64_t stamp = 0;
	stamp = pos *ic->streams[videoStream]->duration;//duration是视频的总长度，乘以pos得到进度条拖动位置对应的视频位置
	int re = av_seek_frame(ic, videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);//向前查找并找到关键帧
	avcodec_flush_buffers(ic->streams[videoStream]->codec);//清空缓冲区

	mutex.unlock();
	if (re >= 0)
		return true;

	return false;
}

bool XFFmpeg::ToRGB(char *out, int outwidth, int outheight)
{
	mutex.lock();
	if (!ic || !yuv)	//判断视频文件被打开没，没被打开的话，直接退出。
	{
		mutex.unlock();
		return false;	
	}
	AVCodecContext *videoCtx = ic->streams[this->videoStream]->codec;//在ic中的streams数组中找到这个codec,
	//打开转码器
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

	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };	//转码的目标数据
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
	av_register_all();		//注册所有的编解码器和文件格式。
}


XFFmpeg::~XFFmpeg()
{
}
