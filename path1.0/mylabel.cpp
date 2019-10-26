#include "mylabel.h"


MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
}


void MyLabel::paintEvent(QPaintEvent *event)
{

    QLabel::paintEvent(event);
    //qDebug() << "abc";
    // 画矩形框
    QPainter paint;
    paint.begin(this);

    paint.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::RoundCap));
    for(int i = 0;i <= NUM_POINTS;i++)
    {
        if(trace_count == 0)
        {
            paint.drawPoint(x_pos[i],y_pos[i]);
        //paint.drawPoint(x_pos[i] + width_car/2,y_pos[i] + height_car/2);
        //paint.drawPoint(x_pos[i] - width_car/2,y_pos[i] - height_car/2);

        }

        if(trace_count == 1)
        {
            paint.drawPoint(x_pos[i],y_pos[i]);
            paint.drawPoint(x_pos1[i],y_pos1[i]);
        //paint.drawPoint(x_pos1[i] + width_car/2,y_pos[i] + height_car/2);
        //paint.drawPoint(x_pos1[i] - width_car/2,y_pos[i] - height_car/2);

        }

        if(trace_count == 2)
        {
            paint.drawPoint(x_pos[i],y_pos[i]);
            paint.drawPoint(x_pos1[i],y_pos1[i]);
            paint.drawPoint(x_pos2[i],y_pos2[i]);
        //paint.drawPoint(x_pos2[i] + width_car/2,y_pos[i] + height_car/2);
        //paint.drawPoint(x_pos2[i] - width_car/2,y_pos[i] - height_car/2);
        }

        paint.drawRect(QRect(x_pos[i] - width_car/2,y_pos[i] - height_car/2,width_car,height_car));
        paint.drawRect(QRect(x_pos1[i] - width_car/2,y_pos1[i] - height_car/2,width_car,height_car));
        paint.drawRect(QRect(x_pos2[i] - width_car/2,y_pos2[i] - height_car/2,width_car,height_car));
        //qDebug()<<width_car<<endl;
    }
    //paint.drawRect(QRect(200, 50, 200, 200));



    paint.end();
}

