#ifndef MISCELLANEOUS_H_INCLUDED
#define MISCELLANEOUS_H_INCLUDED

#include <math.h>


float ConvertAngleToRadian(float);
float ConvertAngleToDegree(float);


float ConvertAngleToRadian(float degree)
{
    return degree * M_PI / 180.0f;
}

float ConvertAngleToDegree(float radian)
{
    return 180.0f * radian / M_PI;
}

#endif // MISCELLANEOUS_H_INCLUDED
