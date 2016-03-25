#include "pm10_cromosome.h"

PM10_Cromosome::PM10_Cromosome()
{
    srand(time(NULL));

    for(int i = 0; i < SIZE_CRME; i++){
        this->genome[i] = (double) rand();
    }
}

double PM10_Cromosome::GetAttitude(){
    return this->attitude;
}

void PM10_Cromosome::CalculateAttitude(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3){
    this->attitude = ((double)bandRefVal_1 * this->genome[0])
                       + ((double)bandRefVal_2 * this->genome[1])
                       + ((double)bandRefVal_3 * this->genome[2]);
}
