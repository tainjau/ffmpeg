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
	///����Ƶ�ļ�������ϴ��Ѿ��򿪾ͻ��ȹر�
	///@path path ��Ƶ�ļ�·��
	///@return bool �ɹ�ʧ�� ʧ����Ϣͨ��GetError��ȡ
	////////////////////////////////////////////////////
	bool Open(const char *path);
	void Close();
	///����ֵ��Ҫ�û�����
	AVPacket Read();

	AVFrame *Decode(const AVPacket *pkt);

	bool ToRGB(const AVFrame *yuv,char *out,int outwidth, int outheight);
	std::string GetError();
	virtual ~XFFmpeg();
	
	int totalMs = 0;	//ʱ��
	int videoStream = 0;
protected:
	
	char errorbuf[1024];
	AVFormatContext *ic = NULL;		//�����Ƶ���������ļ���Ϣ
	AVFrame *yuv = NULL;
	SwsContext *cCtx = NULL;		//����ת����������
	QMutex mutex;
	XFFmpeg();
};

