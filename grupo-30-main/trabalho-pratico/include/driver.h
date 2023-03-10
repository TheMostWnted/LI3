#ifndef ___DRIVER_H___
#define ___DRIVER_H___

#include <stdlib.h>
#include"funcAux.h"
#include "../libs/glibWarningAvoid.h"

/**
\brief Estrutura para representar um Condutor
*/
typedef struct driver* Driver;

typedef struct parScoreViagens* ParScoreViagens;

typedef struct score* Score;

/**
\brief Converte uma string devidamente formatada para um Condutor, sendo este validado dentro da função
@param line Sring com a informação de um Condutor
@param sep separadores usados para distinguir os diferentes campos do Condutor
@returns o Condutor ou NULL se for um Condutor inválido
*/
Driver novoDriver(char* line, char* sep);

Score initScore();

/**
\brief Valida um dado Condutor
@param driver Condutor para validar
@returns 1 caso tenha seja um Condutor válido, 0 caso contrário 
*/
int validaDriver(Driver driver);

/**
\brief Várias funções de gets para obter a informação de um Condutor
*/
char* getDriverId(Driver d);
char* getDrivernome(Driver d);
char* getDriverGenero(Driver d);
char* getDriverDataNascimento(Driver d);
int getClasse_Carro(Driver d);
char* getMatricula(Driver d);
char* getCidade(Driver d);
char* getDriverDataConta(Driver d);
char* getDriverStatusConta(Driver d);
double getDriverScoreTotal(Driver d);
double getTotalAuferido(Driver d);
double getDriverAvaliacaoMedia(Driver d);
int getDriverNumViagens(Driver d);
char* getDriverUltimaViagem(Driver d);
double getScoreCidade(Driver d, char* cidade);

/**
\brief Várias funções para actualizar a informação de um Condutor
*/
void updateDriverAvalicaoMedia(Driver d);
void updateDriverScoreTotal(Driver d, double score);
void updateDriverNumViagens(Driver d);
void updateTotalAuferido(Driver d, double fare, double tip);
void mudarDataDriver(Driver d, char* data);
void updateDriverDataUltimaViagem(char** d, char* data);
void updateScore(Driver d, char* city, double score);


/**
\brief Liberta o espaço ocupado por um Condutor
@param d Apontador para o Condutor a libertar a memória
*/
void deleteDriver(Driver d);
void deleteDriverKey(char* key);
void deleteScoreKey(char* key);
void deleteParScore(Score ps);
void destroiScore(Score s);

/**
\brief Verifica se a hashtable de (Cidade, ParScoreViagens) tem uma entrada para a cidade key
@param d Apontador para o Condutor no qual vai procurar
@param d Apontador para uma string que contém a cidade a procurar
@returns 1 caso encontre, 0 caso contrário
*/
int contemCidade(Driver d, char* key);

void printSc(gpointer key, gpointer value, gpointer userdata);
void printScoreViagem(Score s);
char* printDriver(Driver d, int tamanholinha);

#endif //___DRIVER_H___