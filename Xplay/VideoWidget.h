#pragma once

#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>
class VideoWidget :public QOpenGLWidget		//�̳�QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = NULL);
	void paintEvent(QPaintEvent *e);	//�����ڷ������Ƶ�ʱ�򣬵����������
	void timerEvent(QTimerEvent *e);	//��ʱ��ˢ��
	virtual ~VideoWidget();
};

