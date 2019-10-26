#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QMainWindow>
#include "beziver.h"
#include "mylabel.h"
#include <QStatusBar>
#include <QMouseEvent>

typedef struct POINT
{
    float posx[100];
    float posy[100];
    int number;
}POINT;

extern POINT point;
extern POINT point1;
extern POINT point2;

extern int num_save;//保存的总点数
extern POINT point_out;
extern float width_car;
extern float height_car;
extern int write_flag;
extern float length;

extern int NUM_POINTS;
extern int MAX_SPEED;
extern int MIN_SPEED;
extern int INPUT_NUM;
extern float k_speed;
extern int NUM;
extern int OUT_NUM;

extern float map_width;
extern float map_height;
extern float map_width_pixel;
extern float map_height_pixel;

extern int trace_count;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_input_clicked();

    void on_deletall_clicked();

    void on_showcar_clicked();

    void on_hide_car_clicked();

    void on_write_code_clicked();

    void on_save_points_image_clicked();

    void on_load_clicked();

    void on_plot_clicked();

    void on_load_trace_clicked();

    void on_input_next_clicked();

    void on_load_trace_2_clicked();

    void on_sure_clicked();

    void on_save_points_clicked();

    void on_load_picture_clicked();

    void on_pushButton_open_2_clicked();

    void on_pushButton_send_clicked();

    void SecondarySerialRecvMsgEvent();

    void on_pushButton_clear_clicked();

    void fresh_coms();

    void Msg_exe(QString str);

    void on_refresh_clicked();

    void on_pushButton_send_1_clicked();

    void on_pushButton_send_2_clicked();

    void on_pushButton_send_3_clicked();

private:
    Ui::MainWindow *ui;
    QImage *img;
    QSerialPort *SecondarySerial;             //记得声明你的串口名字！！！！
    QStatusBar* m_pStatus;

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
    //void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H






