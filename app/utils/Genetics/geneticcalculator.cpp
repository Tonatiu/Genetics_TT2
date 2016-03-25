#include "geneticcalculator.h"

using namespace std;

GeneticCalculator::GeneticCalculator(int population_size, double goal)
{
    int size = population_size + (population_size % 2);

    if(population_size > 0){
        this->goal = goal;
        this->populationSize = size;

        this->population = (PM10_Cromosome *) malloc(sizeof(PM10_Cromosome) * size);
        this->banyard = (PM10_Cromosome *) malloc(sizeof(PM10_Cromosome) * size);

        for(int i = 0; i < population_size; i++)
            this->population[i] = PM10_Cromosome();
    }
}

void GeneticCalculator::getPopulationAttitude(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3){
    for(int i = 0; i < this->populationSize; i++){
        this->population[i].CalculateAttitude(bandRefVal_1, bandRefVal_2, bandRefVal_3);
    }
}

void GeneticCalculator::tournament(){
    srand(time(NULL));

    PM10_Cromosome* challenger_1;
    PM10_Cromosome* challenger_2;
    int challenger_1_pos;
    int challenger_2_pos;

    for(int i = 0; i < this->populationSize; i++){
        challenger_1_pos = (rand() % this->populationSize);
        challenger_2_pos = (rand() % this->populationSize);
        //Verifica que las posiciones no sean iguales
        if(challenger_1_pos == challenger_2_pos){
            challenger_2_pos = (rand() % this->populationSize);
            i--;
        }
        else{
            challenger_1 = &this->population[challenger_1_pos];
            challenger_2 = &this->population[challenger_2_pos];

            double difference_1 = challenger_1->attitude - this->goal;
            double difference_2 = challenger_2->attitude - this->goal;

            if(difference_1 < difference_2)
                this->banyard[i] = challenger_1;
            else
                this->banyard[i] = challenger_2;
        }
    }
}

void GeneticCalculator::pairing(){
    srand(time(NULL));
    double fatherMask;
    double motherMask;

    PM10_Cromosome child;
    PM10_Cromosome* father;
    PM10_Cromosome* mother;

    int father_pos;
    int mother_pos;
    int genome_pos;

    for(int i = 0; i < this->populationSize; i++){
        father_pos = (rand() % this->populationSize);
        mother_pos = (rand() % this->populationSize);

        if(father_pos == mother_pos){
            mother_pos = (rand() % this->populationSize);
            i--;
        }
        else{
            fatherMask = (double) rand();
            motherMask = ~fatherMask;

            father = &this->banyard[father_pos];
            mother = &this->banyard[mother_pos];

            for(int j = 0; j < SIZE_CRME; j++){
                genome_pos = rand() % SIZE_CRME;
                child.genome[j] = (father->genome[genome_pos] & fatherMask) | (mother->genome[genome_pos] & motherMask);
            }

            this->population[i] = child;
        }
    }
}

void GeneticCalculator::changeGenomePos(PM10_Cromosome* toMutate){
    srand(time(NULL));

    int times_toSwap = (rand() % 5) + 1;
    int genome_toSwap;
    double aux_value;

    for(int i = 0; i < times_toSwap; i++){
        genome_toSwap = (rand() % 3);
        aux_value = toMutate->genome[1];
        toMutate->genome[1] = toMutate->genome[genome_toSwap];
        toMutate->genome[genome_toSwap] = aux_value;
    }
}

void GeneticCalculator::mutateGenome(PM10_Cromosome *toMutate){
    srand(time(NULL));

    int memsToMutate = (rand() % 3) + 1;
    int memtoMutate;
    double mutationMask;

    for(int i = 0; i < memsToMutate; i++){
        memtoMutate = (rand() % 3);
        mutationMask = (double) rand();

        toMutate->genome[memsToMutate] = toMutate->genome[memsToMutate] ^ mutationMask;
    }
}

void GeneticCalculator::mutation(){
    srand(time(NULL));

    int memsToMutate = rand() % this->populationSize;
    int member_pos;

    for(int i = 0; i < memsToMutate; i++){
        member_pos = rand() % this->populationSize;
        this->changeGenomePos(&this->population[i]);
        this->mutateGenome(&this->population[i]);
    }
}

PM10_Cromosome GeneticCalculator::ObtainEmpiricConstants(char bandRefVal_1, char bandRefVal_2, char bandRefVal_3, int generations){
    srand(time(NULL));

    int probabilityControler = (rand() % 100) + 1;

    for(int i = 0; i < generations; i++){
        this->tournament();
        if((probabilityControler % 2) == 0 && (probabilityControler % 5) == 0){
            this->pairing();
        }
        if(probabilityControler == 3 || probabilityControler == 7 || probabilityControler == 13){
            this->mutation();
        }
    }


}
