#pragma once
extern "C"{
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#include <string>
#include <QMutex>
class XFFmpeg
{
public:
	static XFFmpeg *Get()
	{
		static XFFmpeg ff;
		return &ff;
	}
	////////////////////////////////////////////////////
	///打开视频文件，如果上次已经打开就会先关闭
	///@path path 视频文件路径
	///@return int return total ms
	////////////////////////////////////////////////////
	int Open(const char *path);
	void Close();
	///返回值需要用户清理
	AVPacket Read();

	AVFrame *Decode(const AVPacket *pkt);

	bool ToRGB(char *out,int outwidth, int outheight);

	//pos 0~1 
	bool Seek(float pos);

	std::string GetError();
	virtual ~XFFmpeg();
	
	int totalMs = 0;	//时长
	int fps = 0;		//帧率
	int pts = 0;		//表示当前播放进度
	int videoStream = 0;
protected:
	
	char errorbuf[1024];
	AVFormatContext *ic = NULL;		//存放视频（流）的文件信息
	AVFrame *yuv = NULL;
	SwsContext *cCtx = NULL;		//创建转码器的容器
	QMutex mutex;
	XFFmpeg();
};

