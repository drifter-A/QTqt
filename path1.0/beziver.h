#ifndef BEZIVER_H
#define BEZIVER_H

#endif // BEZIVER_H

#include "mainwindow.h"

void bezier_init(int num_point,int maxspeed,float kspeed,int num_btw_two,int flag);
extern float distance_to_target[1000];
extern float x_pos[1000];
extern float y_pos[1000];
extern float x_pos1[1000];
extern float y_pos1[1000];
extern float x_pos2[1000];
extern float y_pos2[1000];
extern float chassis_speed[1000];
extern float angle_error[1000];
extern float curvity[1000];
extern int speed_each_point[1000];
extern int max_speed_vex[1000];
extern int NUM_POINTS;
extern float max_centripetal_acceleration;


void speed_optimize_curvature_2(int point_number);
void speed_correct();
void max_speed_plan();
void search_for_inflection_point();
