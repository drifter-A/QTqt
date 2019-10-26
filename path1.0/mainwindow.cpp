/*****************************************************************************
Copyright: 2019/6/6 北京邮电大学机器人队
File name: mainwindow.cpp
Description: 主窗口初始化，生成贝塞尔曲线，速度曲线
Author: 徐铭远
Version: 1.0.0
Date: 2018/12/28
History: 2019/6/6 添加注释，增加参数输入编辑框
*****************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QTextBlock>
#include "mylabel.h"
#include<QVBoxLayout>
#include<QGridLayout>
#include<QLayout>
#include "serialform.h"
#include "beziver.h"
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QString"


POINT point;
POINT point1;
POINT point2;

float width_car = 0;
float height_car = 0;
float length = 0;
int NUM_POINTS = 0;
int MAX_SPEED = 1000;
int MIN_SPEED = 100;
int INPUT_NUM = 0;
float k_speed = 0.5;
int NUM = 0;
int OUT_NUM = 0;
float map_width = 6.0;
float map_height = 6.0;
float map_width_pixel = 621;
float map_height_pixel = 621;
int trace_count = 0;

MyLabel *label;

/***************************************************************
  *  @brief     主窗口初始化
  *  @param     parent
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QString picture_path = ui->code_path_edit->text();
    img = new QImage;
    img->load("D:\\robocon\\ground.png");
    //img->load(picture_path);//加载背景图

    label = new MyLabel;
    label->setPixmap(QPixmap::fromImage(*img));//把背景放到自己重写的lable中
    label->resize(img->size());
    label->setGeometry(0,0,img->size().width(),img->size().height());

    //更新像素
    map_width = ui->line_edit_true_width->text().toFloat();
    map_height = ui->line_edit_true_height->text().toFloat();
    map_width_pixel = img->width();
    map_height_pixel = img->height();

    //显示鼠标坐标
    setMouseTracking(true);
    m_pStatus = new QStatusBar();
    setStatusBar(m_pStatus);
    m_pStatus->showMessage("application init ok!");
    //

    QLayout *layout = this->layout();
    layout->addWidget(label);
    fresh_coms();
    ui->Number->setText("0");
}

/***************************************************************
  *  @brief     按键事件
  *  @param     event
  *  @note      回车确认输入坐标
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
    case Qt::Key_Return:
       on_input_clicked();
       ui->posx->setFocus();
       break;
    default:
       QWidget::keyPressEvent(event);
   }
}

/***************************************************************
  *  @brief     释放窗口
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/***************************************************************
  *  @brief     输入坐标点击事件
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
int num_save = 0;//保存的总点数
void MainWindow::on_input_clicked()
{
    if(ui->posx->text().isEmpty()||ui->posy->text().isEmpty()||ui->line_edit_true_width->text().isEmpty()||ui->line_edit_true_height->text().isEmpty())//控制点不能为空
    {
        QMessageBox::warning(NULL, "地图参数初始化失败", "请输入地图实际长宽,分段插入点数", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    map_width = ui->line_edit_true_width->text().toFloat();
    map_height = ui->line_edit_true_height->text().toFloat();
    map_width_pixel = img->width();
    map_height_pixel = img->height();
    if(trace_count == 0)
    {

    point.number = ui->Number->text().toInt();//输入点数
    if(point.number == num_save)
        num_save ++;
    else if(point.number > num_save)
    {
        QMessageBox::warning(NULL, "控制点坐标错误", "请按顺序输入控制点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui->posx->setText("");
        ui->posy->setText("");
        QString num = "";
        num.sprintf("%d",num_save);
        ui->Number->setText(num);
        return;
    }
    point.posx[point.number] = ui->posx->text().toFloat();
    point.posy[point.number] = ui->posy->text().toFloat();

    ui->posx->setText("");
    ui->posy->setText("");
    QString num = "";
    num.sprintf("%d",num_save);
    ui->Number->setText(num);

    ui->point_line_edit->clear();//清空长条编辑框
    for(int i = 0;i< num_save;i++)
    {
        QString str = "";
        str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point.posx[i],point.posy[i]);//提示输入点
        ui->point_line_edit->insertPlainText(str);
    }

    }

    if(trace_count == 1)
    {

        point1.number = ui->Number->text().toInt();//输入点数
        if(point1.number == num_save)
            num_save ++;
        else if(point1.number > num_save)
        {
            QMessageBox::warning(NULL, "控制点坐标错误", "请按顺序输入控制点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            ui->posx->setText("");
            ui->posy->setText("");
            QString num = "";
            num.sprintf("%d",num_save);
            ui->Number->setText(num);
            return;
        }
        point1.posx[point1.number] = ui->posx->text().toFloat();
        point1.posy[point1.number] = ui->posy->text().toFloat();

        ui->posx->setText("");
        ui->posy->setText("");
        QString num = "";
        num.sprintf("%d",num_save);
        ui->Number->setText(num);

        ui->point_line_edit->clear();//清空长条编辑框
        for(int i = 0;i< num_save;i++)
        {
            QString str = "";
            QString str1 = "";

            str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point.posx[i],point.posy[i]);//提示输入点
            str1.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point1.posx[i],point1.posy[i]);//提示输入点

            ui->point_line_edit->insertPlainText(str);
            ui->point_line_edit->insertPlainText(str1);
        }

    }

    if(trace_count == 2)
    {

        point2.number = ui->Number->text().toInt();//输入点数
        if(point2.number == num_save)
            num_save ++;
        else if(point2.number > num_save)
        {
            QMessageBox::warning(NULL, "控制点坐标错误", "请按顺序输入控制点", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            ui->posx->setText("");
            ui->posy->setText("");
            QString num = "";
            num.sprintf("%d",num_save);
            ui->Number->setText(num);
            return;
        }
        point2.posx[point2.number] = ui->posx->text().toFloat();
        point2.posy[point2.number] = ui->posy->text().toFloat();

        ui->posx->setText("");
        ui->posy->setText("");
        QString num = "";
        num.sprintf("%d",num_save);
        ui->Number->setText(num);

        ui->point_line_edit->clear();//清空长条编辑框
        for(int i = 0;i< num_save;i++)
        {
            QString str = "";
            QString str1 = "";
            QString str2 = "";

            str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point.posx[i],point.posy[i]);//提示输入点
            str1.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point1.posx[i],point1.posy[i]);//提示输入点
            str2.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point2.posx[i],point2.posy[i]);//提示输入点

            ui->point_line_edit->insertPlainText(str);
            ui->point_line_edit->insertPlainText(str1);
            ui->point_line_edit->insertPlainText(str2);
        }

    }

    //bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),0);
    QString number_edit;
    number_edit.sprintf("%d",OUT_NUM);
    ui->number->setText(number_edit);

    QString length_edit;
    length_edit.sprintf("%.3f",length);
    ui->length->setText(length_edit);
    //label->update();


}

/***************************************************************
  *  @brief     清空长条编辑框
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_deletall_clicked()
{

    ui->point_line_edit->clear();
    num_save = 0;
    memset(point.posx,0,100);
    memset(point.posy,0,100);
    bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),0);
    QString number_edit;
    number_edit.sprintf("%d",OUT_NUM);
    ui->number->setText(number_edit);

    QString length_edit;
    length_edit.sprintf("%.3f",length);
    ui->length->setText(length_edit);
    label->update();
    ui->Number->setText("0");
    trace_count = 0;
}

/***************************************************************
  *  @brief     显示车
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_showcar_clicked()
{
    if(ui->car_height->text() == ""||ui->car_width->text() == "")
    {
        QMessageBox::warning(NULL, "车子长宽输入错误", "请输入正确长宽", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui->car_height->setText("");
        ui->car_width->setText("");
        return;
    }
    width_car = (ui->car_width->text().toFloat()/map_width)*map_width_pixel;
    height_car = (ui->car_height->text().toFloat()/map_height)*map_height_pixel;
    label->update();
}

/***************************************************************
  *  @brief     隐藏车
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_hide_car_clicked()
{
    width_car = 0;
    height_car = 0;
    label->update();
}

/***************************************************************
  *  @brief     写入代码文档
  *  @param     无
  *  @note      这里之前不知道c有文本输入输出流的函数。。。写的有点麻烦。。。就不优化了
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_write_code_clicked()
{
    bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),1);
    QString length_edit;
    length_edit.sprintf("%.3f",length);
    ui->length->setText(length_edit);

    QString number_edit;
    number_edit.sprintf("%d",OUT_NUM);
    ui->number->setText(number_edit);

    QString str_code_path = ui->code_path_edit->text();
    QFile file(str_code_path);
    if (file.open(QFile::WriteOnly|QFile::Truncate| QIODevice::Text | QIODevice::Append))
    {
        if(num_save == 0)
        {
            QMessageBox::warning(NULL, "wrong", "要存点数为0，写代码文件失败！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            file.close();
            return;
        }
        char*  ch;

        QString temp = "";
        temp.sprintf("#include \"points.h\"\r\nfloat chassis_xpos[%d] = {\r\n",NUM_POINTS);
        QByteArray ba = "";
        ba.append(temp);

        for(int i = 0;i<(num_save-1)*ui->num_btw_two_points->text().toInt()-1;i++)
        {
            QString code = "";
            code.sprintf("%f,",x_pos[i]);
            ba.append(code);
            if(i % 10 == 0&&i!=0)
                ba.append("\r\n");
        }
        QString code_temp = "";
        code_temp.sprintf("%f};\r\n",x_pos[(num_save-1)*ui->num_btw_two_points->text().toInt()-1]);
        ba.append(code_temp);

        temp.sprintf("float chassis_ypos[%d] = {\r\n",NUM_POINTS);
        ba.append(temp);

        for(int i = 0;i<(num_save-1)*ui->num_btw_two_points->text().toInt()-1;i++)
        {
            QString code = "";
            code.sprintf("%f,",y_pos[i]);
            ba.append(code);
            if(i % 10 == 0&&i!=0)
                ba.append("\r\n");
        }
        QString code_temp_2 = "";
        code_temp_2.sprintf("%f};\r\n",y_pos[(num_save-1)*ui->num_btw_two_points->text().toInt()-1]);
        ba.append(code_temp_2);

        temp.sprintf("float chassis_speed_dir[%d] = {\r\n",NUM_POINTS);
        ba.append(temp);
        for(int i = 0;i<(num_save-1)*ui->num_btw_two_points->text().toInt()-1;i++)
        {
            QString code = "";
            code.sprintf("%f,",angle_error[i]);
            ba.append(code);
            if(i % 10 == 0&&i!=0)
                ba.append("\r\n");
        }
        QString code_temp_3 = "";
        code_temp_3.sprintf("%f};\r\n",angle_error[(num_save-1)*ui->num_btw_two_points->text().toInt()-1]);
        ba.append(code_temp_3);

        ch=ba.data();

        file.write(ch);
        file.close();
        QMessageBox::information(NULL, "提示", "写文本代码成功", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }else
        QMessageBox::warning(NULL, "打开失败", "考虑是否未加转义字符'\'？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/***************************************************************
  *  @brief     保存输入点
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_save_points_image_clicked()
{
    QFile file("save.init");
    if (file.open(QFile::WriteOnly|QFile::Truncate| QIODevice::Text | QIODevice::Append))
    {
        char*  ch;
        QByteArray ba = "X\r\n";
        for(int i = 0;i<num_save;i++)
        {
            QString code;
            code.sprintf("%f\r\n",point.posx[i]);
            ba.append(code);
        }

        ba.append("Y\r\n");
        for(int i = 0;i<num_save;i++)
        {
            QString code;
            code.sprintf("%f\r\n",point.posy[i]);
            ba.append(code);
        }

        ch=ba.data();
        file.write(ch);
        file.close();
    }
    QMessageBox::information(NULL, "提示", "保存点成功", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/***************************************************************
  *  @brief     加载输入点
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_load_clicked()
{
    ui->point_line_edit->clear();
    QFile file("save.init");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int count = 0;
        int find_y = 0;
        int num = 0;
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);

            qDebug()<<str<<endl;
            if(str == "X\n")
            {
                count = 0;
                continue;
            }
            if(str == "Y\r\n")
            {
                num = count;
                count = 0;
                find_y = 1;
                continue;
            }
            if(find_y == 0)
            {
                point.posx[count] = str.replace(QString("\r\n"), QString("0")).toFloat();
                //qDebug()<<"x"<<count<<" = "<<point.posx[count]<<endl;
                count++;
            }else
            {
                point.posy[count] = str.replace(QString("\r\n"), QString("0")).toFloat();
                //qDebug()<<"y"<<count<<" = "<<point.posy[count]<<endl;
                count++;
            }


        }
        for(int i = 0;i< num;i++)
        {
            QString str = "";
            str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,point.posx[i],point.posy[i]);
            ui->point_line_edit->insertPlainText(str);
        }
        num_save = num;
        bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),0);
        QString length_edit;
        length_edit.sprintf("%.3f",length);
        ui->length->setText(length_edit);

        QString number_edit;
        number_edit.sprintf("%d",OUT_NUM);
        ui->number->setText(number_edit);

        NUM_POINTS = OUT_NUM;
        label->update();
        file.close();
    }else
      QMessageBox::warning(NULL, "打开失败", "存储文件不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/***************************************************************
  *  @brief     画速度曲线
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void MainWindow::on_plot_clicked()
{
    bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),1);
    serialform *s;
    s = new serialform();//new一下在堆里分配内存，程序退出才被释放窗口才不会消失
    s->show();
}

/***************************************************************
  *  @brief     画生成的曲线
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/9/24/22/00
 **************************************************************/
void MainWindow::on_load_trace_clicked()
{
    bezier_init(num_save,ui->max_speed->text().toInt(),ui->kspeed->text().toFloat(),ui->num_btw_two_points->text().toInt(),0);
    //num_save = 0;
    ui->Number->clear();
    label->update();
}


void MainWindow::on_input_next_clicked()
{
    trace_count = (trace_count + 1) % 3;
}

/***************************************************************
  *  @brief     打印生成的速度点
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/9/25/22/11
 **************************************************************/

void MainWindow::on_load_trace_2_clicked()
{
    ui->point_line_edit->clear();

    if(trace_count == 0)
    {
        for(int i = 0;i <= OUT_NUM;i++)
        {
            QString str = "";
            str.sprintf("第%d个点：X = %.3f   Y = %.3f  Speed = %d   max_speed = %d\r\n",i,x_pos[i] * map_width / map_width_pixel,y_pos[i] * map_width / map_width_pixel,speed_each_point[i],max_speed_vex[i]);//提示输入点
            ui->point_line_edit->insertPlainText(str);
        }
    }

    else if(trace_count == 1)
    {
        for(int i = 0;i <= OUT_NUM;i++)
        {
            QString str = "";
            str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,x_pos1[i] * map_width / map_width_pixel,y_pos1[i] * map_width / map_width_pixel);//提示输入点
            ui->point_line_edit->insertPlainText(str);
        }
    }

    else if(trace_count == 2)
    {
        for(int i = 0;i <= OUT_NUM;i++)
        {
            QString str = "";
            str.sprintf("第%d个点：X = %.3f   Y = %.3f\r\n",i,x_pos2[i] * map_width / map_width_pixel,y_pos2[i] * map_width / map_width_pixel);//提示输入点
            ui->point_line_edit->insertPlainText(str);
        }
    }

}

/***************************************************************
  *  @brief     调节加速度的大小
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/9/25/22/11
 **************************************************************/
void MainWindow::on_sure_clicked()
{
    max_centripetal_acceleration = ui->kspeed_2->text().toInt();
    speed_optimize_curvature_2(NUM_POINTS);
    speed_correct();
    search_for_inflection_point();
    max_speed_plan();
}

/***************************************************************
  *  @brief     保存生成的速度点到文档
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/9/25/22/11
 **************************************************************/
void MainWindow::on_save_points_clicked()
{
    QString address = ui->lineEdit_address->text();
    if(ui->lineEdit_address->text().isEmpty())
    {
        QMessageBox::warning(NULL, "无路径", "请输入生成文件路径", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    QFile file(address);
    if (file.open(QFile::WriteOnly|QFile::Truncate| QIODevice::Text | QIODevice::Append))
    {
        char*  ch;
        int cnt = 1;//每三个点换行
        QByteArray ba = "#include<point.h>";
        ba.append("\r\nPOINT points[] = {\r\n");

        for(int i = 0;i <= NUM_POINTS + 2;i++)
        {
            QString code;
            float a = x_pos[i] * map_width / map_width_pixel;
            float b = y_pos[i] * map_width / map_width_pixel;
            int c = speed_each_point[i];
            if(i <= NUM_POINTS)
            {
               if(cnt % 4 == 0)
                   code.sprintf("{%f,       %f,       %d},\r\n",a,b,c);
               else
                   code.sprintf("{%f,       %f,       %d},\r\n",a,b,c);
            }
            else
            {
                if(i != NUM_POINTS + 2)
                code.sprintf("{%f,       %f,       %d},\r\n,",point.posx[num_save - 1],point.posy[num_save - 1],30);
                else
                code.sprintf("{%f,       %f,       %d}\r\n",point.posx[num_save - 1],point.posy[num_save - 1],30);
            }
            ba.append(code);
            cnt++;
        }
        ba.append("};");

        ch=ba.data();
        file.write(ch);
        file.close();
    }
    QMessageBox::information(NULL, "提示", "保存点成功", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

/***************************************************************
  *  @brief     加载图片
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/7
 **************************************************************/

void MainWindow::on_load_picture_clicked()
{
    QString picture_path = ui->code_path_edit->text();
    img = new QImage;
    img->load(picture_path);//加载背景图

    label = new MyLabel;
    label->setPixmap(QPixmap::fromImage(*img));//把背景放到自己重写的lable中
    label->resize(img->size());
    label->setGeometry(rect().x(),rect().y(),img->size().width(),img->size().height());

    //更新像素
    map_width = ui->line_edit_true_width->text().toFloat();
    map_height = ui->line_edit_true_height->text().toFloat();
    map_width_pixel = img->width();
    map_height_pixel = img->height();

    QLayout *layout = this->layout();
    layout->addWidget(label);

    ui->Number->setText("0");
}

/***************************************************************
  *  @brief     打开串口
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/10
 **************************************************************/
void MainWindow::on_pushButton_open_2_clicked()
{
    if(ui->pushButton_open_2->text()=="打开串口"){
        SecondarySerial=new QSerialPort(this);
        SecondarySerial->setPortName(ui->comboBox_2->currentText());
        SecondarySerial->setBaudRate(ui->comboBox_baudrate_2->currentText().toInt());
        SecondarySerial->setDataBits(QSerialPort::Data8);
        //设置校验位
        SecondarySerial->setParity(QSerialPort::NoParity);
        //设置流控制
        SecondarySerial->setFlowControl(QSerialPort::NoFlowControl);
        //设置停止位
        SecondarySerial->setStopBits(QSerialPort::OneStop);
        SecondarySerial->setReadBufferSize(200000);

        if(SecondarySerial->isOpen())
            {
                QMessageBox msgBox;
                  msgBox.setText("打开成功");
                  msgBox.exec();

            }
        if(SecondarySerial->open(QIODevice::ReadWrite)){

            ui->pushButton_open_2->setText("关闭串口");
            ui->comboBox_2->setDisabled(true);
            ui->comboBox_baudrate_2->setDisabled(true);
           QObject::connect(SecondarySerial, &QSerialPort::readyRead, this, &MainWindow::SecondarySerialRecvMsgEvent);
        }else{
            QMessageBox::about(NULL,"提示","打开串口失败！");
                return ;
        }

       // start_update();
    }else{
        SecondarySerial->close();
        ui->pushButton_open_2->setText("打开串口");

        ui->comboBox_2->setDisabled(false);
        ui->comboBox_baudrate_2->setDisabled(false);
       // stop_update();
    }
}

/***************************************************************
  *  @brief     串口发送消息
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/10
 **************************************************************/
void MainWindow::on_pushButton_send_clicked()
{
    qDebug()<<"send!";
    if(ui->pushButton_open_2->text()!="关闭串口"){
        QMessageBox msgBox;
          msgBox.setText("请先打开串口!");
          msgBox.exec();
                return ;
    }

    QByteArray s=ui->lineEdit_send->text().toLatin1();
    if(ui->checkBox_send_newline->isChecked()){
        s.append('\r');
        s.append('\n');
    }
    SecondarySerial->write(s);
}

/***************************************************************
  *  @brief     串口接收消息
  *  @param     无
  *  @note      无
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/10
 **************************************************************/
float x_pos_real = 0;
float y_pos_real = 0;
void MainWindow::SecondarySerialRecvMsgEvent()
{
    QByteArray temp2;
    //QScrollBar *scrollbar;
    temp2=SecondarySerial->readAll();
   //rx_cnt+=temp.length();
    if(!temp2.isEmpty())
    {
        ui->textEdit_2->setText(ui->textEdit_2->toPlainText()+ '\r\n' + QString(temp2));
        //ui->textEdit_2->append(temp2);
    }
    //temp2.clear();

    char *c = temp2.data();

    if(c[0] == 'X')
    {
       QString str = temp2;
       Msg_exe(str);
       QPainter paint(this);
       paint.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap));
       paint.drawPoint(x_pos_real,y_pos_real);
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->textEdit_2->clear();
}

void MainWindow::fresh_coms(){
    ui->comboBox_2->clear();

    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        ui->comboBox_2->addItem(info.portName());
    }
}

void MainWindow::Msg_exe(QString str)
{
     QString argv[20];
     x_pos_real = str.section(' ',1,1).toFloat();
     y_pos_real = str.section(' ',3,3).toFloat();
}

/***************************************************************
  *  @brief     鼠标单击事件，将点击的地图坐标发送给小车
  *  @param     无
  *  @note      这个函数好像不太好用，而且没必要
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/10
 **************************************************************/
/*void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QString str="("+QString::number(e->x()* map_width / map_width_pixel)+","+QString::number(e->y()* map_width / map_width_pixel)+")";
    m_pStatus->showMessage(tr("单击在：")+str,3000);
}*/

/***************************************************************
  *  @brief     鼠标双击事件，将点击的地图坐标发送给小车
  *  @param     无
  *  @note      原来打算双击后就发送坐标给小车，但是发现这样会出现卡顿，所以改了
  *  @Sample usage     无
  *  @author    钟豪qq:1299766738
  *  @edit      2019/10/10
 **************************************************************/
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e)

{

    //QString str="("+QString::number(e->x()* map_width / map_width_pixel)+","+QString::number(e->y()* map_width / map_width_pixel)+")";

    float x = QString::number(e->x()).toFloat();
    float y = QString::number(e->y()).toFloat();

    x = x * map_width / map_width_pixel;
    y = y * map_width / map_width_pixel;

    QString str1 = QString::number(x, 'f', 3);//保留三位小数转化位QString类型
    QString str2 = QString::number(y, 'f', 3);
    QString str = "("+str1+","+str2+")";

    m_pStatus->showMessage(tr("双击在：")+str,3000);
    ui->lineEdit_send_3->setText("go_to 1 " + str1 +" " + str2);


    /*QByteArray ba = "go_to ";
    QString temp;
    temp.sprintf("%.3f %.3f",x,y);
    ba.append(temp);
    if(ui->checkBox_send_newline->isChecked()){
        ba.append('\r');
        ba.append('\n');
    }
    SecondarySerial->write(ba);
    */
}

void MainWindow::on_refresh_clicked()
{
    fresh_coms();
}

void MainWindow::on_pushButton_send_1_clicked()
{
    qDebug()<<"send!";
    if(ui->pushButton_open_2->text()!="关闭串口"){
        QMessageBox msgBox;
          msgBox.setText("请先打开串口!");
          msgBox.exec();
                return ;
    }

    QByteArray s=ui->lineEdit_send_1->text().toLatin1();
    if(ui->checkBox_send_newline->isChecked())
    {
        s.append('\r');
        s.append('\n');
    }
    SecondarySerial->write(s);
}



void MainWindow::on_pushButton_send_2_clicked()
{
    qDebug()<<"send!";
    if(ui->pushButton_open_2->text()!="关闭串口"){
        QMessageBox msgBox;
          msgBox.setText("请先打开串口!");
          msgBox.exec();
                return ;
    }

    QByteArray s=ui->lineEdit_send_2->text().toLatin1();
    if(ui->checkBox_send_newline->isChecked()){
        s.append('\r');
        s.append('\n');
    }
    SecondarySerial->write(s);
}

void MainWindow::on_pushButton_send_3_clicked()
{
    qDebug()<<"send!";
    if(ui->pushButton_open_2->text()!="关闭串口"){
        QMessageBox msgBox;
          msgBox.setText("请先打开串口!");
          msgBox.exec();
                return ;
    }

    QByteArray s=ui->lineEdit_send_3->text().toLatin1();
    if(ui->checkBox_send_newline->isChecked()){
        s.append('\r');
        s.append('\n');
    }
    SecondarySerial->write(s);
}
