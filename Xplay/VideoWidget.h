#pragma once

#include <QtWidgets/qwidget.h>
#include <QOpenGLWidget>
class VideoWidget :public QOpenGLWidget		//继承QOpenGLWidget
{
public:
	VideoWidget(QWidget *p = NULL);
	void paintEvent(QPaintEvent *e);	//当窗口发生绘制的时候，调用这个函数
	void timerEvent(QTimerEvent *e);	//定时器刷新
	virtual ~VideoWidget();
};

