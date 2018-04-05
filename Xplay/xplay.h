#ifndef XPLAY_H
#define XPLAY_H

#include <QtWidgets/QWidget>
#include "ui_xplay.h"

class Xplay : public QWidget
{
	Q_OBJECT

public:
	Xplay(QWidget *parent = 0);
	~Xplay();
	void timerEvent(QTimerEvent *e);
public slots:
	void open();	//当界面上按钮按下之后，就会执行事先绑定的open函数
	void sliderPressed();//进度条按压处理
	void sliderReleased();//进度条释放处理
private:
	Ui::XplayClass ui;
};

#endif // XPLAY_H
