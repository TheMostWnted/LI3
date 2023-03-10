#ifndef ___DATA_H___
#define ___DATA_H___

#include"catalogoDrivers.h"
#include"catalogoUsers.h"
#include"catalogoRides.h"
#include"stats.h"

/**
\brief Coloca em memória os dados de um ficheiro com condutores numa hashtable com o par (key,data) (id,condutor)
@param ficheiro path para o ficheiro que contém os condutores
@param drivers apontador para uma hashtable de Condutores inicialmente vazia
@param e Catálogo de Estatísticas previamente inicializado a vazio
@param modo inteiro que identifica o modo de utilização do programa (1 - modo interactivo, 2 - modo batch)
@returns 1 caso tenha sido lido com sucesso, 0 caso contrário
*/
int loadDrivers(char* ficheiro, CatDrivers drivers, Estatisticas e, int modo);

/**
\brief Coloca em memória os dados de um ficheiro com utilizadores numa hashtable com o par (key,data) (username,utilizador)
@param ficheiro path para o ficheiro que contém os utilizadores
@param users apontador para uma hashtable de utilizadores inicialmente vazia
@param e Catálogo de Estatísticas previamente inicializado a vazio
@param modo inteiro que identifica o modo de utilização do programa (1 - modo interactivo, 2 - modo batch)
@returns 1 caso tenha sido lido com sucesso, 0 caso contrário
*/
int loadUsers(char* ficheiro, CatUsers users, Estatisticas e, int modo);

/**
\brief Coloca em memória os dados de um ficheiro com viagens numa hashtable com o par (key,data) (id,viagem)
@param ficheiro path para o ficheiro que contém a informação das viagens
@param rides apontador para uma hashtable de viagens inicialmente vazia
@param drivers apontador para uma hashtable de Condutores inicialmente vazia
@param users apontador para uma hashtable de utilizadores inicialmente vazia
@param e Catálogo de Estatísticas previamente inicializado a vazio
@param modo inteiro que identifica o modo de utilização do programa (1 - modo interactivo, 2 - modo batch)
@returns 1 caso tenha sido lido com sucesso, 0 caso contrário
*/
int loadRides(char* ficheiro, CatRides rides, CatDrivers drivers, CatUsers users, Estatisticas e, int modo);

#endif