#ifndef ___RIDES_H___
#define ___RIDES_H___

#include <stdlib.h>
#include "funcAux.h"
#include "../libs/glibWarningAvoid.h"

#define T_BASIC 3.25
#define T_GREEN 4
#define T_PREMIUM 5.2
#define TKM_BASIC 0.62
#define TKM_GREEN 0.79
#define TKM_PREMIUM 0.94

/**
\brief Estrutura para representar uma Ride
*/
typedef struct ride* Ride;

//

Ride novaRide(char* line, char* sep);

//

int validaRide(Ride ride);

//

char* getIdRides (Ride r);

char* getDataViagem (Ride r);

char* getIdDriver (Ride r);

char* getUsername (Ride r);

char* getCity (Ride r);        

int getDistance (Ride r);

double getScoreUser (Ride r);

double getScoreDriver (Ride r);

double getTip (Ride r);

//char* getComment (Ride r);

int getCarClass (Ride r);

//

void updateCarClass (Ride r, int class);

/**
\brief Calcula o custo de uma viagem
@param Viagem a calcular o custo
@returns o custo já calculado para a viagem em questão
*/
double calculaCustoViagem(Ride r);

char* printRide(Ride r, int tamanholinha);

//

void deleteRideKey(char* key);

void deleteRide(Ride r);

#endif //___RIDES_H___
