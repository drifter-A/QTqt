#ifndef MYLABEL_H
#define MYLABEL_H
#include <list>
#include <map>
#include<QLabel>
#include<QPoint>
#include<QMouseEvent>
#include<QPainter>
#include<QWidget>
#include<QDebug>
#include<iostream>
#include<QString>
#include<QImage>
#include<QMainWindow>
#include "beziver.h"
#include "mainwindow.h"
using namespace std;


class MyLabel : public QLabel
{
     Q_OBJECT
public:

    MyLabel(QWidget *parent = 0);


protected:
    void  paintEvent(QPaintEvent *event);
};

#endif // MYLABEL_H
