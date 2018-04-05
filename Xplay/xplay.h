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
	void open();	//�������ϰ�ť����֮�󣬾ͻ�ִ�����Ȱ󶨵�open����
	void sliderPressed();//��������ѹ����
	void sliderReleased();//�������ͷŴ���
private:
	Ui::XplayClass ui;
};

#endif // XPLAY_H
