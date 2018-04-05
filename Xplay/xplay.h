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
public slots:
	void open();	//当界面上按钮按下之后，就会执行事先绑定的open函数

private:
	Ui::XplayClass ui;
};

#endif // XPLAY_H
