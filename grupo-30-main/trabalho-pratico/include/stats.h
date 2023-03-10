#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct userMaisKM* UserMaisKm;

typedef struct totalSpent* Gastos;

typedef struct viagens* MaisViagens;

typedef struct statsViagens* StatsViagens;

/**
*\brief Estrutura para armazenar um Catálogo de Estatísticas
*/
typedef struct stats* Estatisticas;

/**
*\brief Inicializa uma estutura para armazenar um Catálogo de estatísticas
*@return um Catálogo de Estatísticas
*/
Estatisticas initStats();

/**
*\brief Actualiza os dados referentes ao número de Utilizadores num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas a actualizar
*@param total número total de Utilizadores
*/
void updateTotalUsers(Estatisticas e, int total);

/**
*\brief Actualiza os dados referentes ao número de Condutores num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas a actualizar
*@param total número total de Condutores
*/
void updateTotalDrivers(Estatisticas e, int total);

/**
*\brief Actualiza os dados referentes ao número de Viagens num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas a actualizar
*@param total número total de Viagens
*/
void updateTotalRides(Estatisticas e, int total);

/**
*\brief Actualiza os dados referentes aos utilizadores com mais quilómetros, mais gastos e mais viagens num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas previamente preenchido com os utilizadores mais viajado e dispendiso até ao momento
*@param u identificador do utilizador a comparar com aqueles presentemente identificados como sendo o mais viajado e dispendioso no Catálogo de Estatísticas passado por referência
*@param kms número de quilómetros totalizados pelo utilizador passado por referência
*@param dinheiro valor gasto pelo utlizador passado por referência
*@param viagens número de viagens efectuadas pelo utilizador passado por referência
*/
void updateUserStats(Estatisticas e, char* u, double kms, double dinheiro, int viagens);

/**
*\brief Actualiza os dados referentes aos condutores com mais ganhos e mais viagens num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas previamente preenchido com os condutores mais auferido e mais viajado até ao momento
*@param d identificador do condutor a comparar com aqueles presentemente identificados como sendo o mais viajado e auferido no Catálogo de Estatísticas passado por referência
*@param dinheiro valor ganho pelo condutor passado por referência
*@param viagens número de viagens efectuadas pelo condutor passado por referência
*/
void updateDriverStats(Estatisticas e, char* d, double dinheiro, int viagens);

/**
*\brief Actualiza os dados referentes às viagens com maior distância e mais cara num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas previamente preenchido com as viagens mais longo e mais cara até ao momento
*@param id_viagem identificador da viagem a comparar com aquelas presentemente identificadas como sendo a mais longa e mais cara no Catálogo de Estatísticas passado por referência
*@param distancia número de quilómetros da viagem passada por referência
*@param custo tarifa da viagem passada por referência
*/
void updateStatsViagens(Estatisticas e, char* id_viagem, double distancia, double custo);

/**
*\brief Actualiza os dados referentes ao número de viagens das classes das viaturas num Catálogo de Estatísticas
*@param e Catálogo de Estatísticas o número de viagens por cada classe até ao momento
*@param classe classe de viatura a actualizar
*/
void updateStatsClasses(Estatisticas e, int classe);

/**
*\brief Elimina e liberta a memória ocupada pelos dados de um Catálogo de Estatísticas
*@param e Estatísticas a eliminar
*/
void deleteEstatistica(Estatisticas e);

/**
*\brief Imprime um Catálogo de Estatísticas
*@param e Estatísticas a imprimir
*/
void printStats(Estatisticas e);