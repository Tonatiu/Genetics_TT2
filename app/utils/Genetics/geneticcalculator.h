#ifndef GENETICCALCULATOR_H
#define GENETICCALCULATOR_H

#define FACTOR 1.14159265359
#define MM_ERROR 3.335

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "pm10_cromosome.h"

class GeneticCalculator
{
public:
    //Al generar el objeto genera la población inicial
    GeneticCalculator(int population_size, double goal);
    PM10_Cromosome ObtainEmpiricConstants(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3);
private:
    /*Métodos provados*/
    //Calcula la aptitud de los individuos de la población
    void getPopulationAttitude(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3);
    void tournament();
    void pairing();
    /*Métodos que sirven a la mutación*/
    void mutation();
    //Cambia la posición de los genomas del cromosoma
    void changeGenomePos(PM10_Cromosome* toMutate);
    //Realiza una mutación en genomas aleatorios
    void mutateGenome(PM10_Cromosome* toMutate);

    /*Atributos privados*/
    int populationSize;
    double goal;
    PM10_Cromosome* population;
    PM10_Cromosome* banyard;
};

#endif // GENETICCALCULATOR_H
