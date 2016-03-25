#ifndef PM10_CROMOSOME_H
#define PM10_CROMOSOME_H

#define SIZE_CRME 3

#include <stdlib.h>
#include <iostream>
#include <time.h>

class PM10_Cromosome
{
public:
    PM10_Cromosome();
    double GetAttitude();
    void CalculateAttitude(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3);
public:
    double genome[SIZE_CRME];
    double attitude;
};

#endif // PM10_CROMOSOME_H
