#ifndef MISCELLANEOUS_H_INCLUDED
#define MISCELLANEOUS_H_INCLUDED

#include <math.h>


float ConvertAngleToRadian(int angle);



float ConvertAngleToRadian(int angle)
{
    return ((float)angle) * M_PI / 180.0f;
}


#endif // MISCELLANEOUS_H_INCLUDED
