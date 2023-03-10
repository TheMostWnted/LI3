#ifndef ___INTERPRETADOR_H___
#define ___INTERPRETADOR_H___

#include"catalogoDrivers.h"
#include"catalogoUsers.h"
#include"catalogoRides.h"
#include"stats.h"
#include"queries.h"
#include"loaders.h"
#include"funcAux.h"


/**
*\brief Inicia o programa com os ficheiros passados por referência
*@param filename_users string com o caminho para o ficheiro de input de utilizadores
*@param filename_drivers string com o caminho para o ficheiro de input de condutores
*@param filename_rides string com o caminho para o ficheiro de input de viagens
*@param users hashtable de utilizadores previamente inicializada a vazio
*@param drivers hashtable de condutores previamente inicializada a vazio
*@param rides hashtable de viagens previamente inicializada a vazio
*@param e Catálogo de Estatísticas previamente inicializado a vazio
*/
void runProgram(char* filename_users, char* filename_drivers, char* filename_rides, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e);

/**
*\brief Inicia o programa com os ficheiros passados por referência e corre as queries no ficheiro de input
*@param filename_users string com o caminho para o ficheiro de input de utilizadores
*@param filename_drivers string com o caminho para o ficheiro de input de condutores
*@param filename_rides string com o caminho para o ficheiro de input de viagens
*@param queries string com o caminho para o ficheiro de queries a correr
*@param users hashtable de utilizadores previamente inicializada a vazio
*@param drivers hashtable de condutores previamente inicializada a vazio
*@param rides hashtable de viagens previamente inicializada a vazio
*@param e Catálogo de Estatísticas previamente inicializado a vazio
*@returns 1 caso não tenha havido erros, 0 caso contrário
*/
int runQueries(char* filename_users, char* filename_drivers, char* filename_rides, char* queries, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e);

/**
*\brief Apresentador de menu de I/O e interpretador de comandos iniciais
*@param users hashtable de utilizadores previamente inicializada a vazio
*@param drivers hashtable de condutores previamente inicializada a vazio
*@param rides hashtable de viagens previamente inicializada a vazio
*@param e Catálogo de Estatísticas previamente inicializado a vazio
*/
void interpretador(CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e);

/**
*\brief Interpretador de comandos passados por argumento no terminal de forma a correr o modo Batch
*@param input caminho para a pasta onde se encontram as ficheiros de input
*@param queries caminho para o ficheiro contendo as queries a correr
*@param users hashtable de utilizadores previamente inicializada a vazio
*@param drivers hashtable de condutores previamente inicializada a vazio
*@param rides hashtable de viagens previamente inicializada a vazio
*@param e Catálogo de Estatísticas previamente inicializado a vazio
*/
void interpretadorBatch(char* input, char* queries, CatUsers users, CatDrivers drivers, CatRides rides, Estatisticas e);

/**
*\brief Função que imprime um ArrayQuery gerado pela query 2 para um ficheiro
*@param q Estrutura ArrayQuery com a informação a ser impressa
*@param f Apontador para o ficheiro onde a informação será impressa
*/
void printArrayQuery2(ArrayQuery q, FILE *f);

/**
*\brief Função que imprime um ArrayQuery gerado pela query 3 para um ficheiro
*@param q Estrutura ArrayQuery com a informação a ser impressa
*@param f Apontador para o ficheiro onde a informação será impressa
*/
void printArrayQuery3(ArrayQuery q, FILE *f);

/**
*\brief Função que imprime um ArrayQuery gerado pela query 7 para um ficheiro
*@param q Estrutura ArrayQuery com a informação a ser impressa
*@param f Apontador para o ficheiro onde a informação será impressa
*/
void printArrayQuery7(ArrayQuery q, FILE *f);

/**
*\brief Função que imprime a lista de viagens que está na estrutura Catálogos passada por parâmetro
*@param ct Estrutura Catálogos com a informação a ser impressa
*@param f Apontador para o ficheiro onde a informação será impressa
*/
void printQuery8(Catalogos ct, FILE *f);

/**
*\brief Função que imprime a lista de viagens que está na estrutura Catálogos passada por parâmetro
*@param ct Estrutura Catálogos com a informação a ser impressa
*@param f Apontador para o ficheiro onde a informação será impressa
*/
void printQuery9(Catalogos ct, FILE *f);

/**
*\brief Função que pagina a informação devolvida pela query 2 e permite navegação dos resultados
*@param q Estrutura ArrayQuery com a informação a ser impressa
*/
void paginarQuery2(ArrayQuery q);

/**
*\brief Função que pagina a informação devolvida pela query 7 e permite navegação dos resultados
*@param q Estrutura ArrayQuery com a informação a ser impressa
*/
void paginarQuery7(ArrayQuery q);

/**
*\brief Função que pagina a informação devolvida pela query 7 e permite navegação dos resultados
*@param ct Estrutura Catálogos com a informação a ser impressa
*/
void paginarQuery8(Catalogos ct);
#endif