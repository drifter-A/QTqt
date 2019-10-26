/*****************************************************************************
Copyright: 2019/6/6 北京邮电大学机器人队
File name: beziver.cpp
Description: 贝塞尔曲线生成相应函数
Author: 徐铭远
Version: 1.0.0
Date: 2018/12/28
History: 2019/6/6 添加注释，增加参数输入编辑框
*****************************************************************************/
#include "stdio.h"
#include "math.h"
#include "beziver.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#define EXP 2.71828
#define PI 3.14159265
#define MAX_SPEED_fuck 850 //
float max_centripetal_acceleration = 20000; //单位 m/s^2
float k = 1000;
/******************************************************************/
/*!!!!237行改变K有奇效，可以改变轨迹胖瘦，可以对轨迹中几个点的K修改，默认全1*/
/******************************************************************/

typedef struct
{
    float X;
    float Y;
}PointF;

PointF in[100] = {{0,0}};//贝塞尔曲线用户输入的轨迹需要通过的点
PointF out[1000];    // 输出点数组
PointF ctrl_points[100*2-4];//控制点，是输入点的2倍减4
PointF combine_points[4];//两个控制点两个输入点组合成满足二阶贝塞尔曲线生成的四个组合点

float chassis_speed[1000]={0};//底盘的速度存放
float distance_to_target[1000] = {0};//用于计算贝塞尔曲线总长
float angle_error[1000];//用于存放曲线每个点斜率
float x_pos[1000] = {0};//用于存放贝塞尔曲线上的每个点的x
float y_pos[1000] = {0};//用于存放贝塞尔曲线上的每个点的y
float x_pos1[1000] = {0};//用于存放贝塞尔曲线上的每个点的x
float y_pos1[1000] = {0};//用于存放贝塞尔曲线上的每个点的y
float x_pos2[1000] = {0};//用于存放贝塞尔曲线上的每个点的x
float y_pos2[1000] = {0};//用于存放贝塞尔曲线上的每个点的y
float curvity[1000] = {0};//用于存放贝塞尔曲线上的曲率
float speed[1000] = {0};//用于存放速度
int speed_each_point[1000] = {0};
int max_speed_vex[1000] = {0};

void speed_init();//初始化速度
float dis_btw_points(PointF P1,PointF P2);//计算两点间距
void bezier_produce_ctrlpoints(PointF* points);//传入路径上控制点数组和个数
PointF bezier_interpolation_func(float t, PointF* points, int count);//根据组合点计算插入贝塞尔曲线上的点
void draw_bezier_curves(PointF* points, int count, PointF* out_points,int out_count,int start);
float curvature_by_three_points_1(PointF P1 , PointF P2 , PointF P3);
float curvature_by_three_points_2(float X1,float X2,float X3,float Y1,float Y2,float Y3);
void speed_optimize_curvature(int point_number);//根据圆上的三个点求圆的半径，a=V*V/R
void speed_optimize_curvature_2(int point_number);
void speed_correct();
void max_speed_plan();
void search_for_inflection_point();
/***************************************************************
  *  @brief     贝塞尔曲线初始化
  *  @param     num_point:用户输入的路径经过的点的个数
  *  @param     maxspeed:轨迹最大的速度
  *  @param     kspeed:过弯减速比，弧线相对于直线减速的比例，范围0-1，值越大，过弯速度越小
  *  @param     num_btw_two:用户输入的路径经过点两两之间插入的贝塞尔曲线点数
  *  @param     flag:为0表示把实际距离处理成图片相对像素长，用在qt上画图使用。为1表示输出是实际距离，用于输出真是路径点用。
  *  @note      函数结尾调用了speed_init函数，最大速度和减速比两个参数用在里面了，这个速度计算实际用起来感觉还是不太好，希望下一届优化
  *  @Sample usage     用户按要求输入参数后，轨迹的输出存在x_pos,y_pos两个数组中了
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void bezier_init(int num_point,int maxspeed,float kspeed,int num_btw_two,int flag)
{
    if(num_btw_two == 0)//两路径点之间的插入点不能为0
    {
        QMessageBox::warning(NULL, "每段点数不能为0", "请输入正确的数目", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    MAX_SPEED = maxspeed;//最大速度
    INPUT_NUM = num_point;//用户输入点
    k_speed = kspeed;//减速比
    NUM = num_btw_two;//两路径点间的插入点
    OUT_NUM = NUM*(INPUT_NUM-1);//输出点数
    NUM_POINTS = OUT_NUM;//轨迹总点数

    if(flag == 0)//相对像素长
    {
        for(int i = 0;i<num_point;i++)
        {
            if(trace_count == 0)
            {
              in[i].X = (point.posx[i]/map_width)*map_width_pixel;
              in[i].Y = (point.posy[i]/map_height)*map_height_pixel;
            }

            else if(trace_count == 1)
            {
              in[i].X = (point1.posx[i]/map_width)*map_width_pixel;
              in[i].Y = (point1.posy[i]/map_height)*map_height_pixel;
            }

            else if(trace_count == 2)
            {
              in[i].X = (point2.posx[i]/map_width)*map_width_pixel;
              in[i].Y = (point2.posy[i]/map_height)*map_height_pixel;
            }

        }
    }else//实际距离长
    {
        for(int i = 0;i<num_point;i++)
        {
            if(trace_count == 0)
            {
              in[i].X = point.posx[i];
              in[i].Y = point.posy[i];
            }

            else if(trace_count == 1)
            {
              in[i].X = point1.posx[i];
              in[i].Y = point1.posy[i];
            }

            else if(trace_count == 2)
            {
              in[i].X = point2.posx[i];
              in[i].Y = point2.posy[i];
            }

        }
    }

    bezier_produce_ctrlpoints(in);//生成辅助控制点

    for(int j = 0;j<=(INPUT_NUM-1);j++)
        {
            if(j==0)//前三个点用二阶贝塞尔
            {
                combine_points[0] = in [0];
                combine_points[1] = ctrl_points[0];
                combine_points[2] = in [1];
                draw_bezier_curves(combine_points,3,out,NUM,0);// 二阶贝塞尔曲线
            }
            else if(j==INPUT_NUM-2)//最后三个点用二阶贝塞尔
            {
                combine_points[0] = in [j];
                combine_points[1] = ctrl_points[INPUT_NUM*2-5];
                combine_points[2] = in [j+1];
                draw_bezier_curves(combine_points,3,out,NUM,NUM*INPUT_NUM-2*NUM);// 二阶贝塞尔曲线
            }else//中间过程的点用三阶贝塞尔
            {
                combine_points[0] = in [j];
                combine_points[1] = ctrl_points[2*j-1];
                combine_points[2] = ctrl_points[2*j];
                combine_points[3] = in [j+1];
                draw_bezier_curves(combine_points,4,out,NUM,NUM*j);
            }

        }

    /*********计算轨迹总长***********/
    for(int i = 0;i<NUM*(INPUT_NUM-1)-1;i++)
    {
        length += dis_btw_points(out[i],out[i+1]);
    }

    if(flag == 0)//如果是相对像素长则处理成实际距离
        length=(length * map_width / map_width_pixel);

    /*********贝塞尔曲线坐标输出到存放的数组中**********/
    for(int i = 0;i< NUM_POINTS + 1;i++)
    {
        if(trace_count == 0)
        {
            x_pos[i] = out[i].X;
            y_pos[i] = out[i].Y;
        }

        if(trace_count == 1)
        {
            x_pos1[i] = out[i].X;
            y_pos1[i] = out[i].Y;
        }

        if(trace_count == 2)
        {
            x_pos2[i] = out[i].X;
            y_pos2[i] = out[i].Y;
        }
    }

    /*********生成轨迹速度***********/

    speed_optimize_curvature_2(NUM_POINTS);

    /*********速度矫正***********/
    speed_correct();

     /*********最大速度规划***********/
    max_speed_plan();


    /*for(int i =1; i < NUM_POINTS; i++)
    {
        angle_error[i] = atan2((y_pos[i] - y_pos[i - 1]),(x_pos[i] - x_pos[i - 1]));
    }
    angle_error[0] = angle_error[1];

    speed_init();*/

    return;
}

/***************************************************************
  *  @brief     计算贝塞尔曲线插值点
  *  @param     t:步进比例
  *  @param     * points:一阶或二阶贝塞尔曲线的三个或四个联合点
  *  @param     count:一阶的话是一个起点一个终点一个控制点一共三个，二阶的话是一个起点一个终点两个控制点一共四个
  *  @note      理解不了的话参加知乎专栏贝塞尔曲线了解下原理先
  *  @Sample usage     在draw_bezier_curves函数中调用
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
PointF bezier_interpolation_func(float t, PointF* points, int count)
{

    PointF tmp_points[count];
    for (int i = 1; i < count; ++i)
    {
        for (int j = 0; j < count - i; ++j)
        {
            if (i == 1)
            {
                tmp_points[j].X = (float)(points[j].X * (1 - t) + points[j + 1].X * t);
                tmp_points[j].Y = (float)(points[j].Y * (1 - t) + points[j + 1].Y * t);
                continue;
            }
            tmp_points[j].X = (float)(tmp_points[j].X * (1 - t) + tmp_points[j + 1].X * t);
            tmp_points[j].Y = (float)(tmp_points[j].Y * (1 - t) + tmp_points[j + 1].Y * t);
        }
    }
    return tmp_points[0];
}

/***************************************************************
  *  @brief     计算贝塞尔曲线路径点
  *  @param     * points:一阶或二阶贝塞尔曲线的三个或四个联合点
  *  @param     count:一阶的话是一个起点一个终点一个控制点一共三个，二阶的话是一个起点一个终点两个控制点一共四个
  *  @param     * out_points:曲线输出点
  *  @param     out_count:输出点数
  *  @param     start:输出到数组的起始位置，为了多次调用还可以在输出数组中连续索引
  *  @note      理解不了的话参加知乎专栏贝塞尔曲线了解下原理先
  *  @Sample usage     在bezier_init函数中调用
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void draw_bezier_curves(PointF* points, int count, PointF* out_points,int out_count,int start)
{
    float step = 1.0 / out_count;
    float t = 0;
    for(int i=start; i <= (start+out_count); i++)
    {
        PointF temp_point = bezier_interpolation_func(t, points, count);    // 计算插值点
        t += step;
        out_points[i] = temp_point;
    }
}

/***************************************************************
  *  @brief     计算两点间距离
  *  @param     P1:点1
  *  @param     P2:点2
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
float dis_btw_points(PointF P1,PointF P2)
{
    return sqrt((P1.X-P2.X)*(P1.X-P2.X)+(P1.Y-P2.Y)*(P1.Y-P2.Y));
}

/***************************************************************
  *  @brief     贝塞尔曲线产生辅助点
  *  @param     * points传入路径上控制点数组
  *  @note      理解不了的话参加知乎专栏贝塞尔曲线了解下原理先
  *  @Sample usage     在beziver_init调用
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void bezier_produce_ctrlpoints(PointF* points)//传入路径上控制点数组和个数
{
    PointF p1,p2,p3;
    float l1,l2,K;
    for(int i = 0;i < (INPUT_NUM-2);i++)
    {
        p1.X = (points[i].X + points[i+1].X)/2;
        p1.Y = (points[i].Y + points[i+1].Y)/2;
        p2.X = (points[i+1].X + points[i+2].X)/2;
        p2.Y = (points[i+1].Y + points[i+2].Y)/2;//

        l1 = dis_btw_points(points[i],points[i+1]);
        l2 = dis_btw_points(points[i+1],points[i+2]);

        p3.X = (l1*p2.X+l2*p1.X)/(l1+l2);
        p3.Y = (l1*p2.Y+l2*p1.Y)/(l1+l2);

        K = 1;//!!!!!!!!!!!!!!!!!!!!

        ctrl_points[2*i].X = (p1.X - p3.X) * K + points[i+1].X;
        ctrl_points[2*i].Y = (p1.Y - p3.Y) * K + points[i+1].Y ;
        ctrl_points[2*i+1].X = (p2.X - p3.X) * K + points[i+1].X ;
        ctrl_points[2*i+1].Y = (p2.Y - p3.Y) * K + points[i+1].Y ;
    }

}

/***************************************************************
  *  @brief     计算两点斜率
  *  @param     i:数组的第i个数
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
inline float slope_angle(int i)
{
    return atan2(-1*out[i+1].Y-(-1)*out[i].Y,(-1)*out[i+1].X-(-1)*out[i].X);
}

/***************************************************************
  *  @brief     浮点型的abs取绝对值
  *  @param     i:浮点数
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
inline float abs_f(float i)
{
    if(i <= 0)
        i *= -1;

    return i;
}

/***************************************************************
  *  @brief     轨迹斜率初始化
  *  @param     arr:轨迹数组
  *  @param     i:个数
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
inline void slope_init(float arr[],int i)
{
    for(int a = 0;a < i;a++)
    {
        arr[a] = abs_f(slope_angle(a + 1) - slope_angle(a));
        if(arr[a]>6)
            arr[a] = arr[a] - PI * 2;
    }

}

/***************************************************************
  *  @brief     数组搜索最大数
  *  @param     a[]:目标数组
  *  @param     start:起始位置 end:结束位置
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
inline int sort_max(float a[],int start,int end)
{
    float max = a[0];
    int index = 0;
    for(int i=start;i<=end;i++)
        {
            if(a[i] >= max)
                {
                    max=a[i];
                    index=i;
                }
        }
    return index;
}

/***************************************************************
  *  @brief     数组搜索最小数
  *  @param     a[]:目标数组
  *  @param     start:起始位置 end:结束位置
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
inline int sort_min(float a[],int start,int end)
{
    float min = a[0];
    int index = 0;
    for(int i=start;i<=end;i++)
        {
            if(a[i] <= min)
                {
                    min=a[i];
                    index=i;
                }
        }
    return index;
}

/***************************************************************
  *  @brief     计算数组两点间距离
  *  @param     pos:点坐标
  *  @param     i:第几个点
  *  @note      无
  *  @Sample usage     无
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
float cal_two_dis(PointF* pos,int i)
{
    return sqrt((pos[i].X - pos[i+1].X) * (pos[i].X - pos[i+1].X) + (pos[i].Y - pos[i+1].Y) * (pos[i].Y - pos[i+1].Y));
}

/***************************************************************
  *  @brief     轨迹速度初始化
  *  @note      根据曲线最大最小斜率变化率计算轨迹过弯减速多少，一段轨迹
  *  中最小斜率变化率认为是直线段，最大斜率变化率认为是曲率半径最大的地方。
  *  用户给的最大速度默认是直线段的速度，再根据最大最小斜率变化率的差对大斜
  *  率变化率的地方减速。
  *  @Sample usage     调用在beziver_init中
  *  @author    徐铭远qq:863299715
  *  @edit      2019/6/6/14/40
 **************************************************************/
void speed_init()
{
    distance_to_target[NUM_POINTS - 1] = 0;//末尾点距离终点距离为0
    for(int i = NUM_POINTS - 2; i >= 0; i--)//从倒数第二个点开始
    {
        distance_to_target [i] =  distance_to_target[i + 1] + cal_two_dis(out,i);
    }
    slope_init(angle_error,NUM_POINTS - 2);
    float max = angle_error[sort_max(angle_error,0,NUM_POINTS - 3)];
    float min = angle_error[sort_min(angle_error,0,NUM_POINTS - 3)];

    for(int i = 0;i<=NUM_POINTS-2;i++)
    {
        if(angle_error[i] <= 0.00001)//小于两度
            {
                chassis_speed[i] = chassis_speed[i-1];
            }
        else
            chassis_speed[i] = MAX_SPEED - MIN_SPEED - angle_error[i]*(MAX_SPEED-MIN_SPEED)*k_speed/(max-min);
    }
}

/***************************************************************
  *  @brief     曲率计算方法1
  *  @param     PointF P1,P2,P3 分别为前进路上的第一个点，第二个点，和第三个点
  *  @note      此函数配合speed_optimize_curvature使用，用来进行速度规划
  *  @Sample usage     此函数配合speed_optimize_curvature使用
  *  @author    ZX
  *  @edit      2019/9/26
 **************************************************************/
float curvature_by_three_points_1(PointF P1 , PointF P2 , PointF P3){
    float m1, n1;
    float m2, n2;
    float a1, b1;
    float a2, b2;
    float x0, y0;
    float curvity;
    if( ( atan2f( P2.X - P1.X , P2.Y - P1.Y ) ) == atan2f( P3.X - P2.X , P3.Y - P2.Y ) )//三点共线，直接标记曲率为0
        {
            curvity = 0;
            return curvity;
        }

    m1 = (P1.X + P3.X) / 2;
    n1 = (P1.Y + P3.Y) / 2;
    m2 = (P2.X + P3.X) / 2;
    n2 = (P2.Y + P3.Y) / 2;
    a1 = (P3.Y - P1.Y) / (P3.X - P1.X);
    b1 = n1 - a1*m1;
    a2 = (P3.Y - P2.Y) / (P3.X - P2.X);
    b2 = n2 - a2*m2;
    x0 = (b2 - b1) / (a1 - a2);
    y0 = a1 * x0 + b1;
    curvity = sqrt((P1.X-x0)*(P1.X-x0) + (P1.Y-y0)*(P1.Y-y0));
    return curvity;
}

/***************************************************************
  *  @brief     曲率计算方法2
  *  @param     PointF P1,P2,P3 分别为前进路上的第一个点，第二个点，和第三个点
  *  @note      此函数配合speed_optimize_curvature使用，用来进行速度规划
  *  @Sample usage     此函数配合speed_optimize_curvature使用
  *  @author    钟豪
  *  @edit      2019/9/27
 **************************************************************/
float curvature_by_three_points_2(float X1,float X2,float X3,float Y1,float Y2,float Y3){
    float m1, n1;
    float m2, n2;
    float a1, b1;
    float a2, b2;
    float x0, y0;
    float curvity;
    if( ( atan2f( X3 - X1 , Y3 - Y1 ) ) - atan2f( X2 - X1 , Y2 - Y1 ) <= 1e-4 )//三点共线，直接标记曲率为0
        {
            curvity = 0;
            return curvity;
        }
    m1 = (X1 + X3) / 2;
    n1 = (Y1 + Y3) / 2;
    m2 = (X2 + X3) / 2;
    n2 = (Y2 + Y3) / 2;
    a1 = (Y3 - Y1) / (X3 - X1);
    b1 = n1 - a1*m1;
    a2 = (Y3 - Y2) / (X3 - X2);
    b2 = n2 - a2*m2;
    x0 = (b2 - b1) / (a1 - a2);
    y0 = a1 * x0 + b1;
    curvity = sqrt((X1-x0)*(X1-x0) + (Y1-y0)*(Y1-y0));
    if(curvity >= 1e-4)
    curvity = 1 / curvity;
    else
    curvity = 0;

    return curvity;
}

/***************************************************************
  *  @brief     根据曲率计算速度
  *  @param     输入为生成点集的总数
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    ZX
  *  @edit      2019/9/26
 **************************************************************/
void speed_optimize_curvature(int point_number){
    speed_each_point[0] = 125;  //起始速度
    for(int i = 0 ; i < point_number -2 ; i++){
        speed_each_point[i-1] = (int)sqrtf(max_centripetal_acceleration);
        if( fabsf(curvity[i]) < 1e-6){
            speed_each_point[i-1] = MAX_SPEED_fuck;
            continue;
        }
        speed_each_point[i-1] = (int)sqrtf(max_centripetal_acceleration / curvity[i]);
    }
    speed_each_point[point_number - 1] = 50; //最后一个速度是50
}

/***************************************************************
  *  @brief     根据曲率计算速度
  *  @param     输入为生成点集的总数
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    ZX
  *  @edit      2019/9/26
 **************************************************************/
void speed_optimize_curvature_2(int point_number){
    speed_each_point[0] = 125;  //起始速度
    float mid;
    for(int i=2 ; i <= point_number; i++){
        PointF P1={x_pos[i-2],y_pos[i-2]};
        PointF P2={x_pos[i-1],y_pos[i-1]};
        PointF P3={x_pos[i],y_pos[i]};
        float curvity = curvature_by_three_points_1(P1,P2,P3);
        //speed_each_point[i-1] = (int)sqrtf(max_centripetal_acceleration);
        if( fabsf(curvity) >= 1e4 || curvity <= 1e-6)
        {
            speed_each_point[i-1] = speed_each_point[i-2];
            continue;
        }
        mid = sqrtf(max_centripetal_acceleration * curvity);
        if(mid > 850 || mid < -850)
            mid = 850;

        speed_each_point[i-1] = (int)mid;
    }
    speed_each_point[point_number] = 50; //最后一个速度是50
}

/***************************************************************
  *  @brief     如果两点距离过短，就只用一个速度跑
  *  @param     无
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    钟豪
  *  @edit      2019/9/29
 **************************************************************/
void speed_correct()
{
    for(int i = 0; i <= NUM_POINTS - 1; i++)
    {
        /*PointF P1={x_pos[i],y_pos[i]};
        PointF P2={x_pos[i+1],y_pos[i+1]};
        if(dis_btw_points(P1,P2) <= 0.05)
        {
            speed_each_point[i+1] = speed_each_point[i];
        }*/
        if(speed_each_point[i] == -2147483648)
        {
            speed_each_point[i] = speed_each_point[i - 1];
        }
    }

    /*起始的四个点和最后的4个点的速度减小，防止加速度过大*/
    float t = 0.2;
    for(int i = 1; i <= 4; i++)
    {
        speed_each_point[i] = speed_each_point[i] * t;
        t += 0.2;
    }
    t = 0.2;
    for(int i = NUM_POINTS - 1; i >= NUM_POINTS - 4;i--)
    {
        speed_each_point[i] *= t;
        t += 0.2;
    }


}

int max(int x, int y)
{
    if(x >= y)
        return x;
    else
        return y;
}

/***************************************************************
  *  @brief     规划两个点运行间的最大速度
  *  @param     无
  *  @note      先生成速度，之后调用此函数
  *  @Sample usage     生成的速度规划在max_speed_vex数组中，每个速度代表对应点的速度
  *  @author    钟豪
  *  @edit      2019/9/29
 **************************************************************/
void max_speed_plan()
{
    for(int i = 0; i < NUM_POINTS; i++)
    {
        PointF P1={x_pos[i] * map_width / map_width_pixel,y_pos[i] * map_width / map_width_pixel};
        PointF P2={x_pos[i+1] * map_width / map_width_pixel,y_pos[i+1] * map_width / map_width_pixel};
        if(dis_btw_points(P1,P2) >= 0.4)
            max_speed_vex[i] = 850;
        else
        {
            if(fabsf(speed_each_point[i] - speed_each_point[i + 1]) > 400)
                max_speed_vex[i] = max(speed_each_point[i],speed_each_point[i + 1]);
            else
            {
                if(max(speed_each_point[i],speed_each_point[i + 1]) >= 700)
                    max_speed_vex[i] = max(speed_each_point[i],speed_each_point[i + 1]);
                else
                {
                    int v_average = (speed_each_point[i] + speed_each_point[i + 1]) / 2;
                    max_speed_vex[i] = v_average + k * dis_btw_points(P1,P2);
                    if(max_speed_vex[i] > 850)
                        max_speed_vex[i] = 850;
                }
            }
        }
    }

    //search_for_inflection_point();
}

/***************************************************************
  *  @brief     根据运行时间规划速度，行不通
  *  @param     无
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    钟豪
  *  @edit      2019/9/29
 **************************************************************/
/*void acceleration_plan()
{
    for(int i = 0; i < NUM_POINTS; i++)
    {
        PointF P1={x_pos[i],y_pos[i]};
        PointF P2={x_pos[i+1],y_pos[i+1]};
        T = dis_btw_points(P1,P2) / (v2 + v1);
        int dv = v2 - v1;
        v = 1 - cos(PI * t * (v2 + v1) / 2 / dis_btw_points(P1,P2));
        v = v1 + 0.5 * dv * v;
    }

}*/

/***************************************************************
  *  @brief     寻找路径拐点，即在需要速度换向的地方降低速度
  *  @param     无
  *  @note      先生成点集，之后调用此函数
  *  @Sample usage     生成的速度规划在speed_each_point数组中，每个速度代表对应点的速度
  *  @author    钟豪
  *  @edit      2019/9/29
 **************************************************************/
void search_for_inflection_point()
{ 
    for(int i = 0; i <= NUM_POINTS - 1; i++)
    {
        static int temp = 0;
        if(x_pos[temp] - x_pos[temp+1] > 0)
        {
            if(x_pos[i] - x_pos[i+1] <= 0)
            {
                speed_each_point[i] *= 0.2;
                speed_each_point[i-1] *= 0.35;
                speed_each_point[i-2] *= 0.5;
                speed_each_point[i-3] *= 0.7;
                speed_each_point[i-4] *= 0.9;
                temp = i;
            }
        }
        else
        {
            if(x_pos[i] - x_pos[i+1] > 0)
            {
                speed_each_point[i] *= 0.2;
                speed_each_point[i-1] *= 0.35;
                speed_each_point[i-2] *= 0.5;
                speed_each_point[i-3] *= 0.7;
                speed_each_point[i-4] *= 0.9;
                temp = i;
            }
        }
    }
}
